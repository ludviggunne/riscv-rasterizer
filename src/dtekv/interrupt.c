extern void (*__irq_tbl[32])(void);

void register_interrupt(int irq_no, void (*fn)(void))
{
	__irq_tbl[irq_no & 31] = fn;
}
