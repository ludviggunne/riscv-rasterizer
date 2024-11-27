#include <timer_io.h>

void timer_init(void)
{
	TIMER_STATUS = 1; /* reset TO if already set */
	TIMER_CONTROL = 8; /* stop counter if it's already running */
	TIMER_CONTROL = 3; /* set CONT bit, enable interrupts */
}

void timer_start(unsigned int ms)
{
	/* TODO: describe what's going on here */
	unsigned int counter = ms * TIMER_FREQ / 1000;
	TIMER_PERIODL = counter & 0xffff;
	TIMER_PERIODH = counter >> 16;
	TIMER_CONTROL = 4;
}

void timer_clr_int(void)
{
	TIMER_STATUS = 1;
}

