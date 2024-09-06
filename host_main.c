#include <math.h>
#include <stdio.h>
#include "qmath.h"

int qprint(qval_t v)
{
	char s[32];
	int n;

	n = qsnprint(v, s, sizeof(s));
	fputs(s, stdout);

	return n;
}

int qprintln(qval_t v)
{
	int n = qprint(v);

	fputc('\n', stdout);

	return n + 1;
}

int main()
{
	float vbad = NAN;
	float emax = 0;

	for (qval_t i = QVAL(0); i < QVAL(256); i++)
	{
		qval_t q = qsqrt(i);
		float f = sqrtf(QTOF(i));
		float e = QTOF(q) - f;

		if (fabsf(e) > fabsf(emax))
		{
			vbad = QTOF(i);
			emax = e;
		}
	}

	printf("largest error: %+g (for input %g)\n", emax, vbad);

	{
		qval_t f = QVAL(1);
		qval_t v = QVAL(0);

		for (int i = 1; i <= 10; i++)
		{
			v = qadd(v, qdiv(QVAL(1), f));
			f = qmul(f, QINT(i));
		}

		qprintln(v);
	}
}
