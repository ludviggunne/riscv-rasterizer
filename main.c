#include <math.h>
#include <stdio.h>
#include "qmath.h"

void qprint(qval_t v)
{
	printf("%g", v / (float) (1 << QFBITS));

}

int main()
{
	float emax = 0;
	for (qval_t i = -QVAL(M_PI / 4); i < QVAL(M_PI / 4); i++)
	{
		qval_t qt = qtan(i);
		float ft = tan(i / (float) (1 << QFBITS));
		float e = (qt / (float) (1 << QFBITS)) - ft;
		if (fabsf(e) > fabsf(emax))
			emax = e;
		printf("tan(");
		qprint(i);
		printf(") = ");
		qprint(qt);
		printf("(%+g)\n", e);
	}
	printf("largest error: %g\n", emax);
}
