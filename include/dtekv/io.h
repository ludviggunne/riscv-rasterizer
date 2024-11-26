#ifndef IO_H
#define IO_H

#define csrr(csr) \
	({ \
		unsigned int v; \
		asm \
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

#endif
