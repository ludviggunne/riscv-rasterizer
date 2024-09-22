#ifndef MODEL_H
#define MODEL_H

#include <stddef.h>
#include <vmath.h>

typedef struct {
	// Verticex indices
	size_t v0;
	size_t v1;
	size_t v2;
	// Normal indices
	size_t n;
} face_t;

typedef struct {
	// Vertices
	const vec_t *verts;
	size_t nverts;
	// Normals
	const vec_t *norms;
	size_t nnorms;
	// Faces
	const face_t *faces;
	size_t nfaces;
} model_t;

#endif
