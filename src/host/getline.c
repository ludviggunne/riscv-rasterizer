#if !(_POSIX_C_SOURCE >= 200809L)

#include <errno.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

ssize_t
getline(char **restrict lineptr, size_t *restrict n,
	FILE *restrict stream)
{
	ssize_t	r = 0;
	int	c = '\0';

	if (lineptr == NULL || n == NULL || stream == NULL)
	{
		errno = EINVAL;

		return -1;
	}

	if (*lineptr == NULL)
	{
		*n = 64;
		*lineptr = malloc(*n);

		if (*lineptr == NULL)
		{
			errno = ENOMEM;

			return -1;
		}
	}

	for (;;)
	{
		if (c != EOF)
		{
			c = fgetc(stream);

			if (c == EOF)
			{
				return -1;
			}
		}

		if (r == *n)
		{
			size_t	m = *n * 2;
			char *	p = realloc(*lineptr, m);

			if (p == NULL)
			{
				m = *n + 64;
				p = realloc(*lineptr, m);
			}

			if (p == NULL)
			{
				errno = ENOMEM;

				return -1;
			}

			*n = m;
			*lineptr = p;
		}

		if (c == EOF)
		{
			(*lineptr)[r] = '\0';

			break;
		}
		else
		{
			(*lineptr)[r++] = c;

			if (c == '\n')
			{
				c = EOF;
			}
		}
	}

	return r;
}

#endif
