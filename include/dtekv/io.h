#ifndef IO_H
#define IO_H

#define csrr(csr) \
	({ \
		unsigned v; \
		asm volatile \
		( \
			"csrr %0, " #csr ";" \
			: "=r" (v) \
		); \
		v; \
	})

#define csrr64(csr) \
	({ \
		unsigned hi; \
		unsigned lo; \
		unsigned ch; \
		asm volatile \
		( \
			"0:" \
			"csrr %0, " #csr "h;" \
			"csrr %1, " #csr ";" \
			"csrr %2, " #csr "h;" \
			"bne  %0, %2, 0b;" \
			: "=r" (hi), "=r" (lo), "=r" (ch) \
		); \
		((unsigned long long) hi << 32) | (unsigned long long) lo; \
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

#define csrsi(csr, i) \
	({ \
		asm volatile \
		( \
			"csrsi " #csr ", %0;" \
			:: "i" (i) \
		); \
		(void) 0; \
	})

#define csrci(csr, i) \
	({ \
		asm volatile \
		( \
			"csrci " #csr ", %0;" \
			:: "i" (i) \
		); \
		(void) 0; \
	})

#endif
