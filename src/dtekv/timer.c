#include <stddef.h>
#include <init.h>
#include <irq.h>
#include <timer_io.h>

static void (*timer_fn)(void);

static void timer_irq_handler(void)
{
	TIMER_STATUS = 1;

	if (timer_fn != NULL)
	{
		(*timer_fn)();
	}
}

DEFINE_INITCALL(IRQ, timer_init)
{
	register_irq(TIMER_IRQ, timer_irq_handler);
}

void timer_start(unsigned int ms, void (*fn)(void))
{
	int irqf = irq_save();

	timer_fn = fn;

	TIMER_CONTROL = 8;
	TIMER_STATUS = 1;

	if (timer_fn != NULL)
	{
		unsigned long long counter = ms;

		counter = counter * TIMER_FREQ;
		counter = counter / 1000;

		TIMER_PERIODL = counter & 0xFFFF;
		TIMER_PERIODH = counter >> 16;
		TIMER_CONTROL = 7;
	}

	irq_restore(irqf);
}
