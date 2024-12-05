/* By: Ludvig Gunne Lindström */
#ifndef MODEL_H
#define MODEL_H

/* 3D model data.
 * Usually created with obj2c.c
 */

#include <stddef.h>
#include <qmath.h>

typedef struct
{
	qval_t x;
	qval_t y;
	qval_t z;
} vec_t;

typedef struct
{
	/* Vertex indices */
	size_t	v0;
	size_t	v1;
	size_t	v2;
	/* Normal indices */
	size_t	n;
} face_t;

/* Model transform */
typedef struct
{
	/* Roll, pitch, yaw */
	qval_t	r;
	qval_t	p;
	qval_t	y;
	/* Scale */
	qval_t	s;
	/* Translation */
	vec_t	t;
} xfm_t;

typedef struct
{
	/* Vertices */
	const vec_t *	verts;
	size_t		nverts;
	/* Normals */
	const vec_t *	norms;
	size_t		nnorms;
	/* Faces */
	const face_t *	faces;
	size_t		nfaces;
} model_t;

extern model_t **	g_model;
extern xfm_t *		g_model_xfm;

int	model_count(void);
int	model_current(void);
void	model_select(int num);

#endif
