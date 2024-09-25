#ifndef MODEL_H
#define MODEL_H

#include <stddef.h>
#include <qmath.h>
#include <vmath.h>

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

extern model_t *	g_model;
extern xfm_t		g_model_xfm;

#endif
