#include <stddef.h>
#include <button_io.h>
#include <interrupt.h>
#include <irq.h>

static void (*button_fn)(int);

static void button_irq_handler(void)
{
	BUTTON_EDGECAPTURE = 0;

	if (button_fn != NULL)
	{
		(*button_fn)(BUTTON_DATA);
	}
}

void button_set_event(void (*fn)(int))
{
	int irqf = irq_save();

	register_interrupt(BUTTON_IRQ, button_irq_handler);

	button_fn = fn;

	if (button_fn != NULL)
	{
		BUTTON_INTERRUPTMASK = 1;
	}
	else
	{
		BUTTON_INTERRUPTMASK = 0;
		BUTTON_EDGECAPTURE = 0;
	}

	irq_restore(irqf);
}
