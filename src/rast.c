#include <model.h>
#include <qmath.h>
#include <rast.h>
#include <vmath.h>

typedef struct
{
	vec_t	a;
	vec_t	b;
	vec_t	c;
} tri_t;

typedef struct
{
	qval_t	y1;
	qval_t	y2;

	qval_t	lx;
	qval_t	ldxdy;

	qval_t	rx;
	qval_t	rdxdy;

	qval_t	lz;
	qval_t	ldzdy;
	qval_t	dzdx;
} span_t;

static void xfm_vtx(vec_t *v, xfm_t *xfm)
{
	{
		qval_t x = v->x;
		qval_t y = v->y;
		qval_t z = v->z;

		v->x = qadd(qmul( qcos(xfm->r), x), qmul(-qsin(xfm->r), y));
		v->y = qadd(qmul( qsin(xfm->r), x), qmul( qcos(xfm->r), y));
		v->z = z;
	}

	{
		qval_t x = v->x;
		qval_t y = v->y;
		qval_t z = v->z;

		v->x = x;
		v->y = qadd(qmul( qcos(xfm->p), y), qmul(-qsin(xfm->p), z));
		v->z = qadd(qmul( qsin(xfm->p), y), qmul( qcos(xfm->p), z));
	}

	{
		qval_t x = v->x;
		qval_t y = v->y;
		qval_t z = v->z;

		v->x = qadd(qmul( qcos(xfm->y), x), qmul(-qsin(xfm->y), z));
		v->y = y;
		v->z = qadd(qmul( qsin(xfm->y), x), qmul( qcos(xfm->y), z));
	}

	v->x = qadd(qmul(v->x, xfm->s), xfm->t.x);
	v->y = qadd(qmul(v->y, xfm->s), xfm->t.y);
	v->z = qadd(qmul(v->z, xfm->s), xfm->t.z);
}

static void xfm_tri(tri_t *t, xfm_t *xfm)
{
	xfm_vtx(&t->a, xfm);
	xfm_vtx(&t->b, xfm);
	xfm_vtx(&t->c, xfm);
}

static void draw_span(span_t *s, unsigned char *cb, qval_t *zb, int c)
{
	int ix;
	int iy;
	qval_t x;
	qval_t y;
	qval_t z;
	qval_t lx;
	qval_t rx;
	qval_t lz;

	c = ((c & 0xE0) >> 0) | ((c & 0xE0) >> 3) | ((c & 0xC0) >> 6);

	y = s->y1;

	lx = s->lx;
	rx = s->rx;
	lz = s->lz;

	while (y <= s->y2)
	{
#ifdef __riscv
		iy = HEIGHT - 1 - QTOI(y);
#else
		iy = QTOI(y);
#endif

		if (iy >= 0 && iy < HEIGHT)
		{
			x = lx;
			z = lz;

			while (x <= rx)
			{
				ix = QTOI(x);

				if (ix >= 0 && ix < WIDTH)
				{
					if (z < zb[iy * WIDTH + ix])
					{
						zb[iy * WIDTH + ix] = z;
						if (	((ix + iy) & 1) &&
							(c & 0x20) &&
							(c < 0xC0))
						{
							cb[iy * WIDTH + ix] = c + 1;
						}
						else
						{
							cb[iy * WIDTH + ix] = c;
						}
					}
				}

				x = qadd(x, QONE);
				z = qadd(z, s->dzdx);
			}
		}

		y = qadd(y, QONE);
		lx = qadd(lx, s->ldxdy);
		rx = qadd(rx, s->rdxdy);
		lz = qadd(lz, s->ldzdy);
	}
}

static void draw_tri(tri_t *t, unsigned char *cb, qval_t *zb)
{
	static int a = 0;
	a++;

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
	qval_t rx2;
	qval_t lz2;
	qval_t dzdx;

	if (y1 != y2)
	{
		span_t s;

#if 0
		qval_t mdxdy = qdiv(qsub(x3, x1), qsub(y3, y1));
		qval_t mdzdy = qdiv(qsub(z3, z1), qsub(y3, y1));
		qval_t mx = qadd(x1, qmul(mdxdy, qsub(y2, y1)));
		qval_t mz = qadd(z1, qmul(mdzdy, qsub(y2, y1)));
#else
		qval_t mdxdy = qdiv(qsub(x3, x1), qsub(y3, y1));
		qval_t mdzdy = qdiv(qsub(z3, z1), qsub(y3, y1));
		qval_t mx = qadd(x1, qdiv(qmul(qsub(x3, x1), qsub(y2, y1)), qsub(y3, y1)));
		qval_t mz = qadd(z1, qdiv(qmul(qsub(z3, z1), qsub(y2, y1)), qsub(y3, y1)));
#endif

		s.y1 = y1;
		s.y2 = y2;
		s.lx = x1;
		s.rx = x1;
		s.lz = z1;

		if (x2 < mx)
		{
			s.ldxdy = qdiv(qsub(x2, x1), qsub(y2, y1));
			s.rdxdy = mdxdy;
			s.ldzdy = qdiv(qsub(z2, z1), qsub(y2, y1));

			lx2 = x2;
			rx2 = mx;
			lz2 = z2;
		}
		else
		{
			s.ldxdy = mdxdy;
			s.rdxdy = qdiv(qsub(x2, x1), qsub(y2, y1));
			s.ldzdy = mdzdy;

			lx2 = mx;
			rx2 = x2;
			lz2 = mz;
		}

		if (x2 != mx)
		{
			dzdx = qdiv(qsub(mz, z2), qsub(mx, x2));
		}
		else
		{
			dzdx = 0;
		}

		s.dzdx = dzdx;

		draw_span(&s, cb, zb, c);
	}
	else
	{
		if (x1 != x2)
		{
			dzdx = qdiv(qsub(z2, z1), qsub(x2, z1));
		}
		else
		{
			dzdx = 0;
		}

		if (x1 < x2)
		{
			lx2 = x1;
			rx2 = x2;
			lz2 = z1;
		}
		else
		{
			lx2 = x2;
			rx2 = x1;
			lz2 = z2;
		}
	}

	if (y2 != y3)
	{
		span_t s;

		s.y1 = y2;
		s.y2 = y3;
		s.lx = lx2;
		s.rx = rx2;
		s.lz = lz2;

		s.ldxdy = qdiv(qsub(x3, lx2), qsub(y3, y2));
		s.rdxdy = qdiv(qsub(x3, rx2), qsub(y3, y2));
		s.ldzdy = qdiv(qsub(z3, lz2), qsub(y3, y2));
		s.dzdx = dzdx;

		draw_span(&s, cb, zb, c);
	}
}

void draw_model(model_t *mdl, xfm_t *xfm, unsigned char *cb, qval_t *zb)
{
#if 1
	for (int i = 0; i < 2; i++)
	{
		tri_t t =
		{
			mdl->verts[mdl->faces[i].v0],
			mdl->verts[mdl->faces[i].v1],
			mdl->verts[mdl->faces[i].v2],
		};

		xfm_tri(&t, xfm);
		draw_tri(&t, cb, zb);
	}
#else
	span_t s1 =
	{
		.y1	= QVAL( 117.8439788818359375),
		.y2	= QVAL( 173.7781982421875000),

		.lx	= QVAL(  63.9854583740234375),
		.ldxdy	= QVAL(   1.0424652099609375),

		.rx	= QVAL( 239.3686370849609375),
		.rdxdy	= QVAL(-  2.0939483642578125),

		.lz	= QVAL(  12.6127471923828125),
		.ldzdy	= QVAL(   0.2448883056640625),
		.dzdx	= QVAL(-  0.0167541503906250),
	};
	span_t s2 =
	{
		.y1	= QVAL( 117.1258697509765625),
		.y2	= QVAL( 173.7781982421875000),

		.lx	= QVAL( 240.8721466064453125),
		.ldxdy	= QVAL(-  2.0936889648437500),

		.rx	= QVAL( 240.8721466064453125),
		.rdxdy	= QVAL(-  0.6003875732421875),

		.lz	= QVAL(   9.4615173339843750),
		.ldzdy	= QVAL(   0.2973937988281250),
		.dzdx	= QVAL(-  0.0557250976562500),
	};

	draw_span(&s1, cb, zb, 0xFF);
	draw_span(&s2, cb, zb, 0xFF);
#endif
}
