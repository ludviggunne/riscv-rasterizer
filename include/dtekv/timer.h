#ifndef TIMER_H
#define TIMER_H

/* Functions for dealing with timer */

#define MCAUSE_TIMER 16

void timer_init(void);
void timer_start(unsigned int ms);
void timer_clear_interrupt(void);

#endif
