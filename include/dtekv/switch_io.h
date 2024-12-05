/* By: Ludvig Gunne Lindström */
#ifndef SWITCH_IO_H
#define SWITCH_IO_H

#define SWITCH_IRQ		17

extern volatile unsigned	SWITCH_DATA;
extern volatile unsigned	SWITCH_DIRECTION;
extern volatile unsigned	SWITCH_INTERRUPTMASK;
extern volatile unsigned	SWITCH_EDGECAPTURE;

#endif
