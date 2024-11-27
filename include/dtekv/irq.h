#ifndef IRQ_H
#define IRQ_H

#include <io.h>

static inline void irq_enable(void)
{
	csrs(mstatus, 3);
}

static inline void irq_disable(void)
{
	csrc(mstatus, 3);
}

static inline unsigned irq_save(void)
{
	/* stub */
}

static inline void irq_restore(unsigned irqf)
{
	/* stub */
}

#endif
