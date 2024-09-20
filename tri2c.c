/*
 * By: Ludvig Gunne Lindström
 * Last modified: 2024-09-17
 */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>

#include "getline.c"

#include "qmath.h"

#ifdef __riscv
#error what r u doin
#endif

#define ASSERT_USAGE(x)\
	if (!(x)) {\
		usage(stderr, argv[0]);\
		exit(1);\
	}

void usage(FILE *f, const char *name)
{
	fprintf(f, "usage: %s <file> <name> [<comment>]\n", name);
}

int main(int argc, char **argv)
{
	FILE *file;
	FILE *outfile;
	char *path, *name, *comment = NULL, *line = NULL;
	size_t size;

	ASSERT_USAGE(argc > 2);

	path = argv[1];
	name = argv[2];
	if (argc > 3)
	{
		comment = argv[3];
	}

	file = fopen(path, "r");
	if (!file)
	{
		perror("fopen");
		exit(1);
	}

	outfile = stdout;

	time_t t = time(NULL);
	struct tm tm = *localtime(&t);
	fprintf(outfile, "/*\n");
	fprintf(outfile,
	        " * Generated with %s from %s on %d-%02d-%02d\n",
	        __FILE__,
	        path,
		tm.tm_year + 1900,
		tm.tm_mon + 1,
		tm.tm_mday);
	if (comment)
	{
		fprintf(outfile, " * Additional comment: %s\n", comment);
	}
	fprintf(outfile, " */\n\n");
	fprintf(outfile, "#include \"vmath.h\"\n\n");

	if (getline(&line, &size, file) < 0)
	{
		perror("getline");
		exit(1);
	}

	int count;
	sscanf(line, "%d", &count);
	count *= 3;
	fprintf(outfile, "const vec_t %s[%d] = {\n", name, count);

	while (getline(&line, &size, file) >= 0 && count > 0)
	{
		float x, y, z;

		if (strlen(line) <= 1)
		{
			continue;
		}

		if (sscanf(line, "%f%f%f", &x, &y, &z) != 3)
		{
			continue;
		}

		fprintf(outfile, "\tVEC(%d, %d, %d),\n", QVAL(x), QVAL(y), QVAL(z));

		count--;
	}

	fprintf(outfile, "};\n");

	if (outfile != stdout)
	{
		fclose(outfile);
	}
}
