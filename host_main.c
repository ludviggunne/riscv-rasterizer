#include <GL/glew.h>
#include <GL/freeglut.h>
#include <math.h>
#include <stdio.h>
#include "qmath.h"
#include "vmath.h"
#include "uart.h"

int qprint(qval_t v)
{
	char s[32];
	int n;

	n = qsnprint(v, s, sizeof(s));
	fputs(s, stdout);

	return n;
}

int qprintln(qval_t v)
{
	int n = qprint(v);

	fputc('\n', stdout);

	return n + 1;
}

#define MODEL		2
#define WIDTH		320
#define HEIGHT		240
#define SCALE		4

static GLuint		fbo;
static GLuint		tex;
static unsigned char	cb[WIDTH * HEIGHT * 4];
static qval_t		zb[WIDTH * HEIGHT];
static char		keys[256];

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
#elif MODEL == 2
static qval_t mdl_s = QVAL(1);
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

	y = s->y1;

	lx = s->lx;
	lz = s->lz;

	rx = s->rx;
	rz = s->rz;

	while (y <= s->y2)
	{
		iy = QTOI(y);

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

			if (z < zb[iy * WIDTH + ix])
			{
				zb[iy * WIDTH + ix] = z;

				cb[(iy * WIDTH + ix) * 4 + 0] = c;
				cb[(iy * WIDTH + ix) * 4 + 1] = c;
				cb[(iy * WIDTH + ix) * 4 + 2] = c;
			}

			x = qadd(x, QONE);
			z = qadd(z, dzdx);
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
#include "teapot.c"
#elif MODEL == 2
#define RAT_IMPL
#include "rat.h"
#endif

static void display_func(void)
{
	for (int i = 0; i < sizeof(cb) / sizeof*(cb); i++)
	{
		cb[i] = 0;
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
#elif MODEL == 2
	for (int i = 0; i < rat_model.nfaces; i++)
	{
		tri_t t =
		{
			rat_model.verts[rat_model.faces[i].v0],
			rat_model.verts[rat_model.faces[i].v1],
			rat_model.verts[rat_model.faces[i].v2],
		};
		xfm_tri(&t);
		draw_tri(&t);
	}
#endif

	if (keys[GLUT_KEY_LEFT])
	{
		mdl_y = qadd(mdl_y, QVAL(-0.02));
	}
	if (keys[GLUT_KEY_RIGHT])
	{
		mdl_y = qadd(mdl_y, QVAL( 0.02));
	}
	if (keys[GLUT_KEY_UP])
	{
		mdl_p = qadd(mdl_p, QVAL( 0.02));
	}
	if (keys[GLUT_KEY_DOWN])
	{
		mdl_p = qadd(mdl_p, QVAL(-0.02));
	}

	{
		glBindTexture(GL_TEXTURE_2D, tex);
		glTexImage2D(	GL_TEXTURE_2D, 0, GL_RGB,
				WIDTH, HEIGHT, 0, GL_BGRA, GL_UNSIGNED_BYTE,
				cb);
		glBindFramebuffer(GL_READ_FRAMEBUFFER, fbo);
		glFramebufferTexture2D(	GL_READ_FRAMEBUFFER,
					GL_COLOR_ATTACHMENT0,
					GL_TEXTURE_2D, tex, 0);
		glBlitFramebuffer(	0, 0, WIDTH, HEIGHT,
					0, 0, WIDTH * SCALE, HEIGHT * SCALE,
					GL_COLOR_BUFFER_BIT, GL_NEAREST);
		glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);

		glutSwapBuffers();
		glutPostRedisplay();
	}
}

static void keyboard_func(unsigned char key, int x, int y)
{
	if (key >= 'a' && key <= 'z')
	{
		key = key + ('A' - 'a');
	}

	keys[key] = 1;

	if (key == 27)
	{
		glutLeaveMainLoop();
	}
}

static void keyboard_up_func(unsigned char key, int x, int y)
{
	if (key >= 'a' && key <= 'z')
	{
		key = key + ('A' - 'a');
	}

	keys[key] = 0;
}

static void special_func(int key, int x, int y)
{
	keys[key] = 1;
}

static void special_up_func(int key, int x, int y)
{
	keys[key] = 0;
}

static void rast_main(int argc, char *argv[])
{
	glutInit(&argc, argv);

	glutSetOption(	GLUT_ACTION_ON_WINDOW_CLOSE,
			GLUT_ACTION_CONTINUE_EXECUTION);

	glutInitWindowSize(WIDTH * SCALE, HEIGHT * SCALE);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutCreateWindow("");

	glewInit();

	glGenTextures(1, &tex);
	glGenFramebuffers(1, &fbo);

	glutDisplayFunc(display_func);
	glutKeyboardFunc(keyboard_func);
	glutKeyboardUpFunc(keyboard_up_func);
	glutSpecialFunc(special_func);
	glutSpecialUpFunc(special_up_func);

	glutMainLoop();
}

int main(int argc, char *argv[])
{
	float vbad = NAN;
	float emax = 0;

	uart_printf("hello, the number forty-three is %d!\n", 43);
	uart_printf("main is at %p, in case you were wondering.\nargc is %d.\n", main, argc);
	uart_printf("QPI is %q, and thats %s.\n", QPI, "pretty good");
	uart_printf("this is a backslash: \\, and this is a precent sign: %%.\n");

	for (qval_t i = QVAL(0); i < QVAL(256); i++)
	{
		qval_t q = qsqrt(i);
		float f = sqrtf(QTOF(i));
		float e = QTOF(q) - f;

		if (fabsf(e) > fabsf(emax))
		{
			vbad = QTOF(i);
			emax = e;
		}
	}

	printf("largest error: %+g (for input %g)\n", emax, vbad);

	{
		qval_t f = QVAL(1);
		qval_t v = QVAL(0);

		for (int i = 1; i <= 10; i++)
		{
			v = qadd(v, qdiv(QVAL(1), f));
			f = qmul(f, QINT(i));
		}

		qprintln(v);
	}

	rast_main(argc, argv);
}
