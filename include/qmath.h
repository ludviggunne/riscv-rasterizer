#ifndef QMATH_H
#define QMATH_H

typedef int		qval_t;
typedef long long int	qlong_t;
typedef unsigned int	quval_t;

#define QFBITS	16
#define QFMASK	(((quval_t) 1 << QFBITS) - 1)
#define QIBITS	16
#define QIMASK	((((quval_t) 1 << QIBITS) - 1) << QFBITS)

#define QVAL(v)	((qval_t) ((v) * (1 << QFBITS) + 0.5))
#define QINT(v)	((qval_t) ((v) << QFBITS))

#define QTOI(v)	((int) (v) >> QFBITS)
#define QTOF(v)	((float) (v) / (1 << QFBITS))

#define QZERO	QINT(0)
#define QONE	QINT(1)
#define QPI	QVAL(3.14159265358979323846)
#define QPIHALF	(QPI >> 1)
#define QPI4TH	(QPI >> 2)
#define QPI8TH	(QPI >> 3)
#define Q2PI	(QPI << 1)
#define QMAX	0x7FFFFFFF

qval_t	qadd(qval_t a, qval_t b);
qval_t	qsub(qval_t a, qval_t b);
qval_t	qmul(qval_t a, qval_t b);
qval_t	qdiv(qval_t a, qval_t b);
qval_t	qsqrt(qval_t v);
void	qsincos_s(int v, qval_t *sptr, qval_t *cptr);
void	qsincos(qval_t v, qval_t *sptr, qval_t *cptr);
qval_t	qsin(qval_t v);
qval_t	qcos(qval_t v);
qval_t	qtan(qval_t v);
int	qsnprint(qval_t v, char *buf, int len);

#endif
