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
	unsigned irqf = csrr(mstatus);

	irq_disable();

	return irqf;
}

static inline void irq_restore(unsigned irqf)
{
	if ((irqf & (1 << 3)) != 0)
	{
		irq_enable();
	}
}

#endif
