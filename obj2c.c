/*
 * By: Ludvig Gunne Lindström
 * Last modified: Wed Sep 18 04:44:18 PM CEST 2024
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <time.h>
#include <string.h>

#include "model.h"

const char *argv0 = NULL;

void usage(FILE *f)
{
	fprintf(f, "usage: %s FILE MODEL_NAME\n", argv0);
}

typedef union {
	float f;
	size_t i;
} value_t;

typedef struct {
	value_t *data;
	size_t capac;
	size_t size;
} list_t;

void list_push(list_t *l, value_t v)
{
	if (!l->data)
	{
		l->capac = 32;
		l->data = malloc(sizeof(*l->data) * l->capac);
	}

	if (l->size == l->capac)
	{
		l->capac *= 2;
		l->data = realloc(l->data, sizeof(*l->data) * l->capac);
	}

	l->data[l->size++] = v;
}

int startswith(const char *prefix, const char *str)
{
	return strncmp(prefix, str, strlen(prefix)) == 0;
}

int main(int argc, char **argv)
{
	argv0 = argv[0];

	if (argc < 3)
	{
		usage(stderr);
		exit(1);
	}

	const char *fname = argv[1];
	const char *mname = argv[2];
	char *ucname = strdup(mname);
	for (char *ptr = ucname; *ptr; ptr++)
	{
		*ptr = toupper(*ptr);
	}

	FILE *infile = fopen(fname, "r");
	if (!infile)
	{
		perror("fopen");
		exit(1);
	}

	list_t verts = { 0 };
	list_t norms = { 0 };
	list_t faces = { 0 };

	char *line = NULL;
	size_t linesz = 0;
	char *fields;

	while (getline(&line, &linesz, infile) > 0)
	{
		if (startswith("v ", line))
		{
			fields = line + 2;
			float x, y, z;
			sscanf(fields, "%f%f%f", &x, &y, &z);
			list_push(&verts, (value_t) { .f = x });
			list_push(&verts, (value_t) { .f = y });
			list_push(&verts, (value_t) { .f = z });
			continue;
		}

		if (startswith("f ", line))
		{
			fields = line + 2;
			char buf1[64], buf2[64], buf3[64];
			strcpy(buf1, strtok(fields, " "));
			strcpy(buf2, strtok(NULL, " "));
			strcpy(buf3, strtok(NULL, " "));

			size_t v1 = atoll(strtok(buf1, "/")) - 1;
			size_t v2 = atoll(strtok(buf2, "/")) - 1;
			size_t v3 = atoll(strtok(buf3, "/")) - 1;

			list_push(&faces, (value_t) { .i = v1 });
			list_push(&faces, (value_t) { .i = v2 });
			list_push(&faces, (value_t) { .i = v3 });

			float x1 = verts.data[3 * v1 + 0].f;
			float y1 = verts.data[3 * v1 + 1].f;
			float z1 = verts.data[3 * v1 + 2].f;

			float x2 = verts.data[3 * v2 + 0].f;
			float y2 = verts.data[3 * v2 + 1].f;
			float z2 = verts.data[3 * v2 + 2].f;

			float x3 = verts.data[3 * v3 + 0].f;
			float y3 = verts.data[3 * v3 + 1].f;
			float z3 = verts.data[3 * v3 + 2].f;

			x2 -= x1;
			y2 -= y1;
			z2 -= z1;
			x3 -= x1;
			y3 -= y1;
			z3 -= z1;

			float nx, ny, nz;
			nx = y2 * z3 - y3 * z2;
			ny = z2 * x3 - z3 * x2;
			nz = x2 * y3 - x3 * y2;

			float l = sqrtf(nx * nx + ny * ny + nz * nz);
			nx /= l;
			ny /= l;
			nz /= l;

			list_push(&faces, (value_t) { .i = norms.size  / 3});
			list_push(&norms, (value_t) { .f = nx });
			list_push(&norms, (value_t) { .f = ny });
			list_push(&norms, (value_t) { .f = nz });

			continue;
		}
	}

	time_t t = time(NULL);
	struct tm tm = *localtime(&t);

	printf("/*\n");
	printf(" * Generated with %s from %s on %d-%02d-%02d\n",
	       __FILE__, fname,  tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday);
	printf(" */\n");
	printf("\n");
	printf("#ifndef %s_H_INCLUDED\n", ucname);
	printf("#define %s_H_INCLUDED\n", ucname);
	printf("\n");
	printf("#include \"model.h\"\n");
	printf("\n");
	printf("extern model_t %s_model;\n", mname);
	printf("\n");
	printf("#ifdef %s_IMPL\n", ucname);
	printf("\n");
	printf("static const vec_t verts[%zu] = {\n", verts.size / 3);
	for (size_t i = 0; i < verts.size; i += 3)
	{
		printf("\tVEC(%d, %d, %d),\n",
		       QVAL(verts.data[i + 0].f),
		       QVAL(verts.data[i + 1].f),
		       QVAL(verts.data[i + 2].f));
	}
	printf("};\n");
	printf("\n");
	printf("static const vec_t norms[%zu] = {\n", norms.size / 3);
	for (size_t i = 0; i < verts.size; i += 3)
	{
		printf("\tVEC(%d, %d, %d),\n",
		       QVAL(norms.data[i + 0].f),
		       QVAL(norms.data[i + 1].f),
		       QVAL(norms.data[i + 2].f));
	}
	printf("};\n");
	printf("\n");
	printf("static const face_t faces[%zu] = {\n", faces.size / 4);
	for (size_t i = 0; i < faces.size; i += 4)
	{
		printf("\t(face_t) { .v0 = %zu, .v1 = %zu, .v2 = %zu, .n = %zu },\n",
		       faces.data[i + 0].i,
		       faces.data[i + 1].i,
		       faces.data[i + 2].i,
		       faces.data[i + 3].i);
	}
	printf("};\n");
	printf("\n");
	printf("model_t %s_model = (model_t) {\n", mname);
	printf("\t.verts = verts,\n");
	printf("\t.nverts = %zu,\n", verts.size / 3);
	printf("\t.norms = norms,\n");
	printf("\t.nnorms = %zu,\n", norms.size / 3);
	printf("\t.faces = faces,\n");
	printf("\t.nfaces = %zu,\n", faces.size / 4);
	printf("};\n");
	printf("\n");
	printf("#endif\n");
	printf("#endif\n");
}

