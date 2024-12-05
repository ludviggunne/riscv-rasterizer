#ifndef VMATH_H
#define VMATH_H

/* Vector math */

#include <model.h>
#include <qmath.h>

#define VEC(_x, _y, _z) ((vec_t){.x = (_x), .y = (_y), .z = (_z)})

/*
 * Vector addition.
 */
vec_t  vadd(vec_t u, vec_t v);

/*
 * Vector subtraction.
 */
vec_t  vsub(vec_t u, vec_t v);

/*
 * Vector scaling.
 */
vec_t  vscl(vec_t u, qval_t s);

/*
 * Dot product.
 */
qval_t vdot(vec_t u, vec_t v);

/*
 * Cross product.
 */
vec_t  vcrs(vec_t u, vec_t v);

/*
 * Vector length.
 */
qval_t vlen(vec_t u);

#endif /* VMATH_H */
