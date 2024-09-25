#ifndef RAST_H
#define RAST_H

#include <model.h>
#include <qmath.h>
#include <vmath.h>

#define WIDTH	320
#define HEIGHT	240

typedef struct
{
	vec_t	a;
	vec_t	b;
	vec_t	c;
} tri_t;

void draw_model(model_t *mdl, xfm_t *xfm, unsigned char *cb, qval_t *zb);

#endif
