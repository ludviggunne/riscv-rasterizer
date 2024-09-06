#include <math.h>
#include <stdio.h>
#include "qmath.h"

float q_to_float(qval_t v)
{
	return v / (float) (1 << QFBITS);
}

int main()
{
	float vbad = NAN;
	float emax = 0;

	for (qval_t i = QVAL(0); i < QVAL(256); i++)
	{
		qval_t q = qsqrt(i);
		float f = sqrtf(q_to_float(i));
		float e = q_to_float(q) - f;

		if (fabsf(e) > fabsf(emax))
		{
			vbad = q_to_float(i);
			emax = e;
		}
	}

	printf("largest error: %+g (for input %g)\n", emax, vbad);

	{
		char s[16];

		qval_t a = QVAL(1.2);
		qval_t b = QVAL(3.4);
		qval_t c = qmul(a, b);

		qsnprint(c, s, sizeof(s));

		printf("%s\n", s);
	}
}
