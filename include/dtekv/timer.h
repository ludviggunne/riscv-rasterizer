#ifndef TIMER_H
#define TIMER_H

/* Functions for dealing with timer */

void timer_init(void);
void timer_start(unsigned int ms);
void timer_clr_int(void);

#endif
