#ifndef BUTTON_IO_H
#define BUTTON_IO_H

#define BUTTON_IRQ		18

extern volatile unsigned	BUTTON_DATA;
extern volatile unsigned	BUTTON_DIRECTION;
extern volatile unsigned	BUTTON_INTERRUPTMASK;
extern volatile unsigned	BUTTON_EDGECAPTURE;

#endif
