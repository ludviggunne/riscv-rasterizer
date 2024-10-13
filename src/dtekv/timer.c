#include <timer.h>

#define TIMER_BASE ((volatile int *)0x04000020)
#define FREQ 29999999


void timer_init(void)
{
  *TIMER_BASE = 1; // reset TO if already set
  *(TIMER_BASE+1) = 8; // stop counter if it's already running
  *(TIMER_BASE+1) = 3; // set CONT bit, enable interrupts

}

void timer_start(unsigned int ms)
{
  unsigned int counter = ms * FREQ / 1000;
  *(TIMER_BASE+2) = counter & 0xffff;
  *(TIMER_BASE+3) = counter >> 16;
  *(TIMER_BASE+1) = 4;
}

void timer_clear_interrupt(void)
{
	*TIMER_BASE = 1;
}

