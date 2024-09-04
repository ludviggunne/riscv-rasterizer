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

	for (qval_t i = QVAL(32760); i < QVAL(32767); i++)
	{
		qval_t q = qsqrt(i);
		float f = sqrtf(q_to_float(i));
		float e = q_to_float(q) - f;

		if (fabsf(e) > fabsf(emax))
		{
			vbad = q_to_float(i);
			emax = e;
		}

#if 0
		printf("sqrt(%g) = %g (%+g)\n",
			q_to_float(i), q_to_float(q), e);
#endif
	}

	printf("largest error: %+g (for input %g)\n", emax, vbad);
}
