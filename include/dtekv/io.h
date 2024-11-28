#ifndef IO_H
#define IO_H

#define csrr(csr) \
	({ \
		unsigned int v; \
		asm volatile \
		( \
			"csrr %0, " #csr ";" \
			: "=r" (v) \
		); \
		v; \
	})

#define csrw(csr, v) \
	({ \
		asm volatile \
		( \
			"csrw " #csr ", %0;" \
			:: "r" (v) \
		); \
		(void) 0; \
	})

#define csrs(csr, i) \
	({ \
		asm volatile \
		( \
			"csrs " #csr ", %0;" \
			:: "i" (i) \
		); \
		(void) 0; \
	})

#define csrc(csr, i) \
	({ \
		asm volatile \
		( \
			"csrc " #csr ", %0;" \
			:: "i" (i) \
		); \
		(void) 0; \
	})

#endif
