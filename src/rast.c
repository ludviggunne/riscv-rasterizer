#include <model.h>
#include <perf.h>
#include <qmath.h>
#include <rast.h>

#define Z_NEAR		QVAL(1)
#define CLAMP(x)	((x) > 255 ? 255 : (x))

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
	qval_t	lz;
	qval_t	ldzdy;

	qval_t	rx;
	qval_t	rdxdy;
	qval_t	rz;
	qval_t	rdzdy;
} span_t;

typedef struct
{
	int	num;
	vec_t *	dir;
	vec_t *	col;
} light_t;

static vec_t		xfm_vert[10000];
static unsigned char	norm_col[10000][2];
static int		light_num;
static light_t		lights[] =
{
	/* Natural-ish light */
	{
		2,
		(vec_t [])
		{
			{ QVAL( 0.7071), QVAL( 0.0000), QVAL( 0.7071) },
			{ QVAL(-0.7071), QVAL( 0.0000), QVAL( 0.7070) },
		},
		(vec_t [])
		{
			{ QVAL(0.80), QVAL(0.80), QVAL(0.60) },
			{ QVAL(0.60), QVAL(0.60), QVAL(0.80) },
		},
	},
	/* Bisexual light */
	{
		3,
		(vec_t [])
		{
			{ QVAL( 0.0000), QVAL( 0.0000), QVAL( 1.0000) },
			{ QVAL( 0.7071), QVAL( 0.0000), QVAL( 0.7071) },
			{ QVAL(-0.7071), QVAL( 0.0000), QVAL( 0.7070) },
		},
		(vec_t [])
		{
			{ QVAL(0.10), QVAL(0.10), QVAL(0.10) },
			{ QVAL(0.80), QVAL(0.00), QVAL(0.20) },
			{ QVAL(0.20), QVAL(0.00), QVAL(1.00) },
		},
	},
	/* RGB light */
	{
		3,
		(vec_t [])
		{
			{ QVAL( 0.0000), QVAL(-0.5000), QVAL( 0.8660) },
			{ QVAL(-0.7071), QVAL( 0.0000), QVAL( 0.7070) },
			{ QVAL( 0.7071), QVAL( 0.0000), QVAL( 0.7071) },
		},
		(vec_t [])
		{
			{ QVAL(1.00), QVAL(0.00), QVAL(0.00) },
			{ QVAL(0.00), QVAL(0.75), QVAL(0.00) },
			{ QVAL(0.00), QVAL(0.00), QVAL(1.00) },
		},
	},
	/* Spooky light */
	{
		1,
		(vec_t [])
		{
			{ QVAL( 0.0000), QVAL( 0.7071), QVAL( 0.7071) },
		},
		(vec_t [])
		{
			{ QVAL(0.25), QVAL(0.10), QVAL(1.00) },
		},
	},
};

int light_count(void)
{
	return sizeof(lights) / sizeof*(lights);
}

int light_current(void)
{
	return light_num;
}

void light_select(int n)
{
	light_num = n;
}

static
void draw_span(span_t *s, unsigned char c[], unsigned char *cb, qval_t *zb)
{
	PROFILE_WINDOW_START(triangle_span);

	int ix;
	int iy;
	int ci;
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
#ifdef __riscv
		iy = HEIGHT - 1 - QTOI(y);
#else
		iy = QTOI(y);
#endif

		if (iy >= 0 && iy < HEIGHT)
		{
			x = lx & ~0xFFFF;
			z = lz;
			ci = (QTOI(x) ^ QTOI(y)) & 1;


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
						cb[iy * WIDTH + ix] = c[ci];
					}
				}

				x = qadd(x, QONE);
				z = qadd(z, dzdx);
				ci = ci ^ 1;
			}
		}

		y = qadd(y, QONE);
		lx = qadd(lx, s->ldxdy);
		rx = qadd(rx, s->rdxdy);
		lz = qadd(lz, s->ldzdy);
		rz = qadd(rz, s->rdzdy);
	}

	PROFILE_WINDOW_END(triangle_span);
}

static
void draw_tri(tri_t *t, unsigned char c[], unsigned char *cb, qval_t *zb)
{
	/* near culling */
	if (t->a.z < Z_NEAR || t->b.z < Z_NEAR || t->c.z < Z_NEAR)
	{
		return;
	}

	{
		/* backface culling */
		qval_t s = 0;

		s = qadd(s, qmul(t->a.x, qsub(t->b.y, t->c.y)));
		s = qadd(s, qmul(t->b.x, qsub(t->c.y, t->a.y)));
		s = qadd(s, qmul(t->c.x, qsub(t->a.y, t->b.y)));

		if (s >= 0)
		{
			return;
		}
	}

	PROFILE_WINDOW_START(triangle);

	vec_t v1 = t->a;
	vec_t v2 = t->b;
	vec_t v3 = t->c;

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

		draw_span(&s, c, cb, zb);
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

		draw_span(&s, c, cb, zb);
	}

	PROFILE_WINDOW_END(triangle);
}

void draw_model(model_t *mdl, xfm_t *xfm, unsigned char *cb, qval_t *zb)
{
	PROFILE_WINDOW_START(model);

	PROFILE_WINDOW_START(model_xfm);

	qval_t rs, rc;
	qval_t ps, pc;
	qval_t ys, yc;
	qval_t z_norm = QVAL(0.01);

	qsincos(xfm->r, &rs, &rc);
	qsincos(xfm->p, &ps, &pc);
	qsincos(xfm->y, &ys, &yc);

	for (int i = 0; i < mdl->nverts; i++)
	{
		const vec_t *	v = &mdl->verts[i];
		vec_t *		w = &xfm_vert[i];

		{
			qval_t x = v->x;
			qval_t y = v->y;
			qval_t z = v->z;

			w->x = qadd(qmul( rc, x), qmul(-rs, y));
			w->y = qadd(qmul( rs, x), qmul( rc, y));
			w->z = z;
		}

		{
			qval_t x = w->x;
			qval_t y = w->y;
			qval_t z = w->z;

			w->x = x;
			w->y = qadd(qmul( pc, y), qmul(-ps, z));
			w->z = qadd(qmul( ps, y), qmul( pc, z));
		}

		{
			qval_t x = w->x;
			qval_t y = w->y;
			qval_t z = w->z;

			w->x = qadd(qmul( yc, x), qmul(-ys, z));
			w->y = y;
			w->z = qadd(qmul( ys, x), qmul( yc, z));
		}

		w->x = qadd(qmul(w->x, xfm->s), xfm->t.x);
		w->y = qadd(qmul(w->y, xfm->s), xfm->t.y);
		w->z = qadd(qmul(w->z, xfm->s), xfm->t.z);		

		if (w->z < Z_NEAR)
		{
			continue;
		}

		w->x = qadd(qdiv(w->x, qmul(w->z, z_norm)), QINT(WIDTH / 2));
		w->y = qadd(qdiv(w->y, qmul(w->z, z_norm)), QINT(HEIGHT / 2));
	}

	for (int i = 0; i < mdl->nnorms; i++)
	{
		vec_t	n = mdl->norms[i];
		int	r = 0;
		int	g = 0;
		int	b = 0;

		{
			qval_t x = n.x;
			qval_t y = n.y;
			qval_t z = n.z;

			n.x = qadd(qmul( rc, x), qmul(-rs, y));
			n.y = qadd(qmul( rs, x), qmul( rc, y));
			n.z = z;
		}

		{
			qval_t x = n.x;
			qval_t y = n.y;
			qval_t z = n.z;

			n.x = x;
			n.y = qadd(qmul( pc, y), qmul(-ps, z));
			n.z = qadd(qmul( ps, y), qmul( pc, z));
		}

		{
			qval_t x = n.x;
			qval_t y = n.y;
			qval_t z = n.z;

			n.x = qadd(qmul( yc, x), qmul(-ys, z));
			n.y = y;
			n.z = qadd(qmul( ys, x), qmul( yc, z));
		}

		for (int j = 0; j < lights[light_num].num; j++)
		{
			vec_t *d = &lights[light_num].dir[j];
			vec_t *c = &lights[light_num].col[j];
			qval_t m;

			m = QZERO;
			m = qadd(m, qmul(n.x, d->x));
			m = qadd(m, qmul(n.y, d->y));
			m = qadd(m, qmul(n.z, d->z));

			if (m >= 0)
			{
				continue;
			}

			m = qmul(m, -QINT(255));
			r += QTOI(qmul(c->x, m));
			g += QTOI(qmul(c->y, m));
			b += QTOI(qmul(c->z, m));
		}

		norm_col[i][0] = 0;
		norm_col[i][0] = norm_col[i][0] | ((CLAMP(r) >> 5) << 5);
		norm_col[i][0] = norm_col[i][0] | ((CLAMP(g) >> 5) << 2);
		norm_col[i][0] = norm_col[i][0] | ((CLAMP(b) >> 6) << 0);

		norm_col[i][1] = 0;
		norm_col[i][1] = norm_col[i][1] | ((CLAMP(r + 15) >> 5) << 5);
		norm_col[i][1] = norm_col[i][1] | ((CLAMP(g + 15) >> 5) << 2);
		norm_col[i][1] = norm_col[i][1] | ((CLAMP(b +  7) >> 6) << 0);
	}

	PROFILE_WINDOW_END(model_xfm);

	for (int i = 0; i < mdl->nfaces; i++)
	{
		tri_t t =
		{
			xfm_vert[mdl->faces[i].v0],
			xfm_vert[mdl->faces[i].v1],
			xfm_vert[mdl->faces[i].v2],
		};

		draw_tri(&t, norm_col[mdl->faces[i].n], cb, zb);
	}

	PROFILE_WINDOW_END(model);
}
