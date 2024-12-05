/* By: Ludvig Gunne Lindström */
#ifndef IRQ_H
#define IRQ_H

#include <csr.h>

static inline void irq_enable(void)
{
	csrsi(mstatus, 3);
}

static inline void irq_disable(void)
{
	csrci(mstatus, 3);
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
