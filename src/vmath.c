#include <vmath.h>

vec_t vadd(vec_t u, vec_t v)
{
	vec_t w;
	w.x = qadd(u.x, v.x);
	w.y = qadd(u.y, v.y);
	w.z = qadd(u.z, v.z);
	return w;
}

vec_t vsub(vec_t u, vec_t v)
{
	vec_t w;
	w.x = qsub(u.x, v.x);
	w.y = qsub(u.y, v.y);
	w.z = qsub(u.z, v.z);
	return w;
}

vec_t vscl(vec_t u, qval_t s)
{
	vec_t w;
	w.x = qmul(u.x, s);
	w.y = qmul(u.y, s);
	w.z = qmul(u.z, s);
	return w;
}

qval_t vdot(vec_t u, vec_t v)
{
	qval_t d = QZERO;
	d = qadd(d, qmul(u.x, v.x));
	d = qadd(d, qmul(u.y, v.y));
	d = qadd(d, qmul(u.z, v.z));
	return d;
}

vec_t vcrs(vec_t u, vec_t v)
{
	vec_t w;
	w.x = qsub(qmul(u.y, v.z), qmul(u.z, v.y));
	w.y = qsub(qmul(u.z, v.x), qmul(u.x, v.z));
	w.z = qsub(qmul(u.x, v.y), qmul(u.y, v.x));
	return w;
}

qval_t vlen(vec_t u)
{
	qval_t a = QZERO;
	a = qadd(a, qmul(u.x, u.x));
	a = qadd(a, qmul(u.y, u.y));
	a = qadd(a, qmul(u.z, u.z));
	return qsqrt(a);
}
