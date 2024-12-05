/* By: Ludvig Gunne Lindström */
#ifndef TIMER_IO_H
#define TIMER_IO_H

#define TIMER_IRQ		16
#define TIMER_FREQ		29999999

extern volatile unsigned	TIMER_STATUS;
extern volatile unsigned	TIMER_CONTROL;
extern volatile unsigned	TIMER_PERIODL;
extern volatile unsigned	TIMER_PERIODH;
extern volatile unsigned	TIMER_SNAPL;
extern volatile unsigned	TIMER_SNAPH;

#endif
