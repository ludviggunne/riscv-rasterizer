#ifndef VGA_H
#define VGA_H

#define VGA_WIDTH		320
#define VGA_HEIGHT		240

extern void *volatile		VGA_FRONT;
extern void *volatile		VGA_BACK;
extern volatile unsigned	VGA_RES;
extern volatile unsigned	VGA_STATUS;
extern unsigned char		VGA_MEM[2][VGA_WIDTH * VGA_HEIGHT];

#endif
