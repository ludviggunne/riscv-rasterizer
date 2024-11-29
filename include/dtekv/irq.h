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
	unsigned irqf = csrr(mstatus) & (1 << 3);

	irq_disable();

	return irqf;
}

static inline void irq_restore(unsigned irqf)
{
	if (irqf)
	{
		irq_enable();
	}
}

void register_irq(int irq_no, void (*fn)(void));

#endif
