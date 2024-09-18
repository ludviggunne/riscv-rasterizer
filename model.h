#ifndef MODEL_H
#define MODEL_H

#include "vmath.h"
#include <stddef.h>

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
	vec_t *verts;
	size_t nverts;
	// Normals
	vec_t *norms;
	size_t nnorms;
	// Faces
	face_t *faces;
	size_t nfaces;
} model_t;

#endif
