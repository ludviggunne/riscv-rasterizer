#include <stdlib.h>
#include <string.h>
#include <stdio.h>

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
	fprintf(f, "usage: %s <file> <name>\n", name);
}

int main(int argc, char **argv)
{
	FILE *file;
	FILE *outfile;
	char *path, *name, *line = NULL;
	size_t size;

	ASSERT_USAGE(argc > 2);

	path = argv[1];
	name = argv[2];

	file = fopen(path, "r");
	if (!file)
	{
		perror("fopen");
		exit(1);
	}

	outfile = stdout;

	fprintf(outfile, "#include \"qmath.h\"\n\n");

	if (getline(&line, &size, file) < 0)
	{
		perror("getline");
		exit(1);
	}

	int count;
	sscanf(line, "%d", &count);
	fprintf(outfile, "const qval_t %s[%d] = {\n", name, count * 3);

	while (getline(&line, &size, file) >= 0 && count-- > 0)
	{
		if (strlen(line) == 0)
		{
			continue;
		}

		float x, y, z;
		sscanf(line, "%f%f%f", &x, &y, &z);

		fprintf(outfile, "%12d, %12d, %12d,\n", QVAL(x), QVAL(y), QVAL(z));
	}

	fprintf(outfile, "};\n");

	if (outfile != stdout)
	{
		fclose(outfile);
	}
}
