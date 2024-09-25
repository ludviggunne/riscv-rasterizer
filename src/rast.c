#include <model.h>
#include <qmath.h>
#include <rast.h>
#include <vmath.h>

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

static void draw_span(span_t *s, unsigned char *cb, qval_t *zb, int c)
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
						cb[iy * WIDTH + ix] = c;
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

static void draw_tri(tri_t *t, unsigned char *cb, qval_t *zb)
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

		draw_span(&s, cb, zb, c);
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

		draw_span(&s, cb, zb, c);
	}
}

void draw_model(model_t *mdl, xfm_t *xfm, unsigned char *cb, qval_t *zb)
{
	for (int i = 0; i < mdl->nfaces; i++)
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
}
