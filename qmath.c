#include "qmath.h"

qval_t qadd(qval_t a, qval_t b)
{
	return a + b;
}

qval_t qsub(qval_t a, qval_t b)
{
	return a - b;
}

qval_t qmul(qval_t a, qval_t b)
{
#ifdef __riscv
	unsigned hi;
	unsigned lo;
	__asm__
	(
		"mulh %0, %1, %2;" :
		"=r"(hi) :
		"r"(a), "r"(b)
	);
	__asm__
	(
		"mul %0, %1, %2;" :
		"=r"(lo) :
		"r"(a), "r"(b)
	);
	return (hi << 16) | (lo >> 16);
#else
	qval_t hi = ((qlong_t) a * (qlong_t) b) >> QFBITS;
	qval_t lo = (a * b) >> QFBITS;
	qval_t v = (hi & QIMASK) | (lo & QFMASK);
	return v;
#endif
}

qval_t qdiv(qval_t a, qval_t b)
{
	int s = 0;

	if (a < 0)
	{
		s = !s;
		a = -a;
	}

	if (b < 0)
	{
		s = !s;
		b = -b;
	}

	quval_t m = (quval_t) -1 / (quval_t) b + 1;
	quval_t q = qmul(a, m);

	if (s)
	{
		return -(qval_t) q;
	}
	else
	{
		return (qval_t) q;
	}
}

qval_t qsqrt(qval_t v)
{
	qval_t r;

	if (v < QONE)
	{
		quval_t b = 1 << (QFBITS - 1);

		r = (1 << QFBITS) - 1;

		while (b != 0)
		{
			qval_t p = r ^ b;

			if (qmul(p, p) >= v)
			{
				r = p;
			}

			b = b >> 1;
		}
	}
	else if (v > QONE)
	{
		quval_t b = 1 << ((QIBITS >> 1) + QFBITS - 1);

		r = 0;

		while (b > v)
		{
			b = b >> 1;
		}

		while (b != 0)
		{
			qval_t p = r ^ b;
			qval_t q = qmul(p, p);

			if (0 <= q && q <= v)
			{
				r = p;
			}

			b = b >> 1;
		}
	}
	else
	{
		r = QONE;
	}

	return r;
}

#include "qsintbl.c"

static qval_t qsin_s(int v)
{
	qval_t r;
	int s = 0;

	v = v & 0x3FFFF;

	if (v >= 0x20000)
	{
		v = v - 0x20000;
		s = !s;
	}

	if (v >= 0x10000)
	{
		v = 0x20000 - v;
	}

	if (v >= 0x0FF5E)
	{
		r = QONE;
	}
	else
	{
		r = qsintbl[v];
	}

	if (s)
	{
		return -r;
	}
	else
	{
		return r;
	}
}

#define RAD_MUL 0.636619772367

qval_t qsin(qval_t v)
{
	return qsin_s(qmul(v, QVAL(RAD_MUL)));
}

qval_t qcos(qval_t v)
{
	return qsin_s(qmul(v, QVAL(RAD_MUL)) + 0x10000);
}

qval_t qtan(qval_t v)
{
	return qdiv(qsin(v), qcos(v));
}

int qsnprint(qval_t v, char *buf, int len)
{
	int n = 0;

	if (v < 0)
	{
		v = -v;

		if (n++ < len)
		{
			*buf++ = '-';
		}
	}

	{
		int i = v >> QFBITS;
		char c[8];
		int m = 0;

		if (i == 0)
		{
			c[m++] = '0';
		}
		else
		{
			while (i != 0)
			{
				c[m++] = '0' + (i % 10);
				i = i / 10;
			}
		}

		while (m != 0)
		{
			m--;

			if (n++ < len)
			{
				*buf++ = c[m];
			}
		}
	}

	{
		int f = v & QFMASK;
		char c;

		if (f != 0)
		{
			if (n++ < len)
			{
				*buf++ = '.';
			}

			while (f != 0)
			{
				f = f * 10;
				c = '0' +  (f >> QFBITS);
				f = (f & QFMASK);

				if (n++ < len)
				{
					*buf++ = c;
				}
			}
		}
	}

	if (n < len)
	{
		*buf++ = '\0';
	}

	return n;
}
