#include "display.h"
#include "qmath.h"
#include "uart.h"
#include "vmath.h"

static void display_qval(qval_t v)
{
	char s[8];
	int p = 0;

	qsnprint(v, s, sizeof(s));

	for (int i = 0; i < 6; i++)
	{
		if (s[p] == '\0')
		{
			display_char(i, ' ');
		}
		else if (s[p + 1] == '.')
		{
			display_char(i, s[p] | 0x80);
			p = p + 2;
		}
		else
		{
			display_char(i, s[p]);
			p = p + 1;
		}
	}
}

#define MODEL			5
#define WIDTH			320
#define HEIGHT			240

extern void *volatile		VGA_FRONT;
extern void *volatile		VGA_BACK;
extern volatile unsigned	VGA_RES;
extern volatile unsigned	VGA_STATUS;
extern unsigned char		VGA_MEM[2][WIDTH * HEIGHT];

static int			frame_count;
static unsigned char		(*cb)[WIDTH * HEIGHT];
static qval_t			zb[WIDTH * HEIGHT];

typedef struct
{
	vec_t	a;
	vec_t	b;
	vec_t	c;
} tri_t;

static qval_t mdl_r = QZERO;
static qval_t mdl_p = QZERO;
static qval_t mdl_y = QZERO;
#if MODEL == 0
static qval_t mdl_s = QVAL(1);
#elif MODEL == 1
static qval_t mdl_s = QVAL(8);
#elif MODEL == 2 || MODEL == 3
static qval_t mdl_s = QVAL(1);
#elif MODEL == 4
static qval_t mdl_s = QVAL(0.01);
#elif MODEL == 5
static qval_t mdl_s = QVAL(0.05);
#endif
static vec_t mdl_xlat = { QVAL(0), QVAL(0), QVAL(25) };

static void xfm_vtx(vec_t *v)
{
	{
		qval_t x = v->x;
		qval_t y = v->y;
		qval_t z = v->z;

		v->x = qadd(qmul( qcos(mdl_r), x), qmul(-qsin(mdl_r), y));
		v->y = qadd(qmul( qsin(mdl_r), x), qmul( qcos(mdl_r), y));
		v->z = z;
	}

	{
		qval_t x = v->x;
		qval_t y = v->y;
		qval_t z = v->z;

		v->x = x;
		v->y = qadd(qmul( qcos(mdl_p), y), qmul(-qsin(mdl_p), z));
		v->z = qadd(qmul( qsin(mdl_p), y), qmul( qcos(mdl_p), z));
	}

	{
		qval_t x = v->x;
		qval_t y = v->y;
		qval_t z = v->z;

		v->x = qadd(qmul( qcos(mdl_y), x), qmul(-qsin(mdl_y), z));
		v->y = y;
		v->z = qadd(qmul( qsin(mdl_y), x), qmul( qcos(mdl_y), z));
	}

	v->x = qadd(qmul(v->x, mdl_s), mdl_xlat.x);
	v->y = qadd(qmul(v->y, mdl_s), mdl_xlat.y);
	v->z = qadd(qmul(v->z, mdl_s), mdl_xlat.z);
}

static void xfm_tri(tri_t *t)
{
	xfm_vtx(&t->a);
	xfm_vtx(&t->b);
	xfm_vtx(&t->c);
}

typedef struct
{
	qval_t	y1;
	qval_t	y2;

	qval_t	lx;
	qval_t	ldxdy;
	qval_t	lz;
	qval_t	ldzdy;

	qval_t	rx;
	qval_t	rdxdy;
	qval_t	rz;
	qval_t	rdzdy;
} span_t;

static void draw_span(span_t *s, int c)
{
	int ix;
	int iy;
	qval_t x;
	qval_t y;
	qval_t z;
	qval_t lx;
	qval_t lz;
	qval_t rz;
	qval_t rx;
	qval_t dzdx;

	c = ((c & 0xE0) >> 0) | ((c & 0xE0) >> 3) | ((c & 0xC0) >> 6);

	y = s->y1;

	lx = s->lx;
	lz = s->lz;

	rx = s->rx;
	rz = s->rz;

	while (y <= s->y2)
	{
		iy = QTOI(y);

		if (iy >= 0 && iy < HEIGHT)
		{
			x = lx & ~0xFFFF;
			z = lz;

			if (lx != rx)
			{
				dzdx = qdiv(qsub(rz, lz), qsub(rx, lx));
			}
			else
			{
				dzdx = 0;
			}

			while (x <= rx)
			{
				ix = QTOI(x);

				if (ix >= 0 && ix < WIDTH)
				{
					if (z < zb[iy * WIDTH + ix])
					{
						zb[iy * WIDTH + ix] = z;

						(*cb)[iy * WIDTH + ix] = c;
					}
				}

				x = qadd(x, QONE);
				z = qadd(z, dzdx);
			}
		}

		y = qadd(y, QONE);
		lx = qadd(lx, s->ldxdy);
		rx = qadd(rx, s->rdxdy);
		lz = qadd(lz, s->ldzdy);
		rz = qadd(rz, s->rdzdy);
	}
}

static void draw_tri(tri_t *t)
{
	vec_t v1 = t->a;
	vec_t v2 = t->b;
	vec_t v3 = t->c;

	vec_t n;
	{
		vec_t u = vsub(v2, v1);
		vec_t v = vsub(v3, v1);

		{
			qval_t l = vlen(u);

			if (l == 0)
			{
				return;
			}

			u = vscl(u, qdiv(QONE, l));
		}
		{
			qval_t l = vlen(v);

			if (l == 0)
			{
				return;
			}

			v = vscl(v, qdiv(QONE, l));
		}

		n = vcrs(u, v);
		n = vscl(n, qdiv(QONE, vlen(n)));
	}
	if (n.z > 0)
	{
		return;
	}
	int c = QTOI(qmul(n.z, QVAL(-255)));

	qval_t z_norm = QVAL(0.01);
	v1.x = qadd(qdiv(v1.x, qmul(v1.z, z_norm)), QINT(WIDTH / 2));
	v1.y = qadd(qdiv(v1.y, qmul(v1.z, z_norm)), QINT(HEIGHT / 2));
	v2.x = qadd(qdiv(v2.x, qmul(v2.z, z_norm)), QINT(WIDTH / 2));
	v2.y = qadd(qdiv(v2.y, qmul(v2.z, z_norm)), QINT(HEIGHT / 2));
	v3.x = qadd(qdiv(v3.x, qmul(v3.z, z_norm)), QINT(WIDTH / 2));
	v3.y = qadd(qdiv(v3.y, qmul(v3.z, z_norm)), QINT(HEIGHT / 2));

	if (v1.y > v2.y)
	{
		vec_t v = v1;
		v1 = v2;
		v2 = v;
	}
	if (v2.y > v3.y)
	{
		vec_t v = v2;
		v2 = v3;
		v3 = v;
	}
	if (v1.y > v2.y)
	{
		vec_t v = v1;
		v1 = v2;
		v2 = v;
	}

	qval_t x1 = v1.x;
	qval_t y1 = v1.y;
	qval_t z1 = v1.z;
	qval_t x2 = v2.x;
	qval_t y2 = v2.y;
	qval_t z2 = v2.z;
	qval_t x3 = v3.x;
	qval_t y3 = v3.y;
	qval_t z3 = v3.z;

	qval_t lx2;
	qval_t lz2;
	qval_t rx2;
	qval_t rz2;

	if (y1 != y2)
	{
		span_t s;

		qval_t mdxdy = qdiv(qsub(x3, x1), qsub(y3, y1));
		qval_t mdzdy = qdiv(qsub(z3, z1), qsub(y3, y1));
		qval_t mx = qadd(x1, qmul(mdxdy, qsub(y2, y1)));
		qval_t mz = qadd(z1, qmul(mdzdy, qsub(y2, y1)));

		s.y1 = y1;
		s.y2 = y2;
		s.lx = x1;
		s.lz = z1;
		s.rx = x1;
		s.rz = z1;

		if (x2 < mx)
		{
			s.ldxdy = qdiv(qsub(x2, x1), qsub(y2, y1));
			s.ldzdy = qdiv(qsub(z2, z1), qsub(y2, y1));
			s.rdxdy = mdxdy;
			s.rdzdy = mdzdy;

			lx2 = x2;
			lz2 = z2;
			rx2 = mx;
			rz2 = mz;
		}
		else
		{
			s.ldxdy = mdxdy;
			s.ldzdy = mdzdy;
			s.rdxdy = qdiv(qsub(x2, x1), qsub(y2, y1));
			s.rdzdy = qdiv(qsub(z2, z1), qsub(y2, y1));

			lx2 = mx;
			lz2 = mz;
			rx2 = x2;
			rz2 = z2;
		}

		draw_span(&s, c);
	}
	else
	{
		if (x1 < x2)
		{
			lx2 = x1;
			lz2 = z1;
			rx2 = x2;
			rz2 = z2;
		}
		else
		{
			lx2 = x2;
			lz2 = z2;
			rx2 = x1;
			rz2 = z1;
		}
	}

	if (y2 != y3)
	{
		span_t s;

		s.y1 = y2;
		s.y2 = y3;
		s.lx = lx2;
		s.lz = lz2;
		s.rx = rx2;
		s.rz = rz2;

		s.ldxdy = qdiv(qsub(x3, lx2), qsub(y3, y2));
		s.ldzdy = qdiv(qsub(z3, lz2), qsub(y3, y2));
		s.rdxdy = qdiv(qsub(x3, rx2), qsub(y3, y2));
		s.rdzdy = qdiv(qsub(z3, rz2), qsub(y3, y2));

		draw_span(&s, c);
	}
}

#if MODEL == 1
# include "teapot.c"
#elif MODEL == 2
# define RAT_IMPL
# include "rat.h"
static const model_t *mdl = &rat_model;
#elif MODEL == 3
# define RAT_LOFI_IMPL
# include "rat_lofi.h"
static const model_t *mdl = &rat_lofi_model;
#elif MODEL == 4
# define MODERN_IMPL
# include "modern.h"
static const model_t *mdl = &modern_model;
#elif MODEL == 5
# define TORUS_IMPL
# include "torus.h"
static const model_t *mdl = &torus_model;
#endif

static void display_func(void)
{
	for (int i = 0; i < sizeof(*cb) / sizeof*(*cb); i++)
	{
		__asm__ ("sb zero, %0;" : "=m"((*cb)[i]));
	}

	for (int i = 0; i < sizeof(zb) / sizeof*(zb); i++)
	{
		zb[i] = QMAX;
	}

#if MODEL == 0
	tri_t tris[] =
	{
		/* Front */
		{
			VEC(QVAL(-10), QVAL( 10), QVAL(-10)),
			VEC(QVAL( 10), QVAL( 10), QVAL(-10)),
			VEC(QVAL( 10), QVAL(-10), QVAL(-10)),
		},
		{
			VEC(QVAL(-10), QVAL( 10), QVAL(-10)),
			VEC(QVAL( 10), QVAL(-10), QVAL(-10)),
			VEC(QVAL(-10), QVAL(-10), QVAL(-10)),
		},
		/* Right */
		{
			VEC(QVAL( 10), QVAL( 10), QVAL(-10)),
			VEC(QVAL( 10), QVAL( 10), QVAL( 10)),
			VEC(QVAL( 10), QVAL(-10), QVAL( 10)),
		},
		{
			VEC(QVAL( 10), QVAL( 10), QVAL(-10)),
			VEC(QVAL( 10), QVAL(-10), QVAL( 10)),
			VEC(QVAL( 10), QVAL(-10), QVAL(-10)),
		},
		/* Back */
		{
			VEC(QVAL( 10), QVAL( 10), QVAL( 10)),
			VEC(QVAL(-10), QVAL( 10), QVAL( 10)),
			VEC(QVAL(-10), QVAL(-10), QVAL( 10)),
		},
		{
			VEC(QVAL( 10), QVAL( 10), QVAL( 10)),
			VEC(QVAL(-10), QVAL(-10), QVAL( 10)),
			VEC(QVAL( 10), QVAL(-10), QVAL( 10)),
		},
		/* Left */
		{
			VEC(QVAL(-10), QVAL( 10), QVAL( 10)),
			VEC(QVAL(-10), QVAL( 10), QVAL(-10)),
			VEC(QVAL(-10), QVAL(-10), QVAL(-10)),
		},
		{
			VEC(QVAL(-10), QVAL( 10), QVAL( 10)),
			VEC(QVAL(-10), QVAL(-10), QVAL(-10)),
			VEC(QVAL(-10), QVAL(-10), QVAL( 10)),
		},
		/* Top */
		{
			VEC(QVAL(-10), QVAL( 10), QVAL( 10)),
			VEC(QVAL( 10), QVAL( 10), QVAL( 10)),
			VEC(QVAL( 10), QVAL( 10), QVAL(-10)),
		},
		{
			VEC(QVAL(-10), QVAL( 10), QVAL( 10)),
			VEC(QVAL( 10), QVAL( 10), QVAL(-10)),
			VEC(QVAL(-10), QVAL( 10), QVAL(-10)),
		},
		/* Bottom */
		{
			VEC(QVAL(-10), QVAL(-10), QVAL(-10)),
			VEC(QVAL( 10), QVAL(-10), QVAL(-10)),
			VEC(QVAL( 10), QVAL(-10), QVAL( 10)),
		},
		{
			VEC(QVAL(-10), QVAL(-10), QVAL(-10)),
			VEC(QVAL( 10), QVAL(-10), QVAL( 10)),
			VEC(QVAL(-10), QVAL(-10), QVAL( 10)),
		},
	};

	for (int i = 0; i < sizeof(tris) / sizeof*(tris); i++)
	{
		tri_t *t = &tris[i];
		xfm_tri(t);
		draw_tri(t);
	}
#elif MODEL == 1
	for (int i = 0; i < sizeof(teapot) / sizeof*(teapot); i += 3)
	{
		tri_t t =
		{
			teapot[i + 0],
			teapot[i + 1],
			teapot[i + 2],
		};
		xfm_tri(&t);
		draw_tri(&t);
	}
#elif MODEL >= 2
	for (int i = 0; i < mdl->nfaces; i++)
	{
		tri_t t =
		{
			mdl->verts[mdl->faces[i].v0],
			mdl->verts[mdl->faces[i].v1],
			mdl->verts[mdl->faces[i].v2],
		};
		xfm_tri(&t);
		draw_tri(&t);
	}
#endif

	mdl_y = qadd(mdl_y, QVAL( 0.02));
	mdl_p = qadd(mdl_p, QVAL( 0.02));

	{
		while (VGA_STATUS & 1)
		{
		}

		VGA_BACK = cb;
		VGA_FRONT = cb;

		cb = &VGA_MEM[frame_count++ & 1];
	}
}

static void rast_main(int argc, char *argv[])
{
	cb = &VGA_MEM[1];

	for (;;)
	{
		display_func();
	}
}


int main(int argc, char *argv[])
{
#if 1
	/* enable button interrupt */
	*(volatile int *)0x040000d8 = -1;
	/* enable button edge trigger */
	*(volatile int *)0x040000dc = -1;
#endif

	uart_init();
	uart_printf("hello, the number forty-three is %d!\n", 43);
	uart_printf("main is at %p, in case you were wondering.\nargc is %d.\n", main, argc);
	uart_printf("QPI is %q, and thats %s.\n", QPI, "pretty good");
	uart_printf("this is a backslash: \\, and this is a precent sign: %%.\n");

	{
		qval_t f = QVAL(1);
		qval_t v = QVAL(0);

		for (int i = 1; i <= 10; i++)
		{
			v = qadd(v, qdiv(QVAL(1), f));
			f = qmul(f, QINT(i));
		}

		display_qval(v);
	}

	rast_main(argc, argv);
}
