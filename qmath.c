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
		"mulh %0, %2, %3;"
		"mul  %1, %2, %3;" :
		"=r"(hi), "=r"(lo) :
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
		r = QVAL(1);
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
