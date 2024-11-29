#ifndef RAST_H
#define RAST_H

#include <model.h>
#include <qmath.h>

#define WIDTH	320
#define HEIGHT	240

void draw_model(model_t *mdl, xfm_t *xfm, unsigned char *cb, qval_t *zb);

#endif
