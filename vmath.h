#ifndef VMATH_H
#define VMATH_H

#include "qmath.h"

#define VEC(_x, _y, _z) ((vec_t){.x = (_x), .y = (_y), .z = (_z)})

typedef struct
{
	qval_t x;
	qval_t y;
	qval_t z;
}
vec_t;

vec_t  vadd(vec_t u, vec_t v);
vec_t  vsub(vec_t u, vec_t v);
vec_t  vscl(vec_t u, qval_t s);
qval_t vdot(vec_t u, vec_t v);
vec_t  vcrs(vec_t u, vec_t v);

#define				/* VMATH_H */
