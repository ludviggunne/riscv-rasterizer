#ifndef INTERRUPT_H
#define INTERRUPT_H

void register_interrupt(int irq_no, void (*fn)(void));

#endif
