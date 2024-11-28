	.text
	.globl	_reset
_reset:
	/* initialize global pointer */
	.option	push
	.option	norelax
	la	gp, __global_pointer$
	.option	pop

	/* enable interrupts */
	csrs	mie, 3		/* msie */
	csrs	mie, 7		/* mtie */
	csrs	mie, 11		/* meie */
	csrs	mstatus, 3	/* mie */

	/* clear bss */
	la	t2, __bss_start
	la	t3, __bss_end
	bge	t2, t3, 1f
0:
	sw	zero, 0(t2)
	addi	t2, t2, 4
	bne	t2, t3, 0b
1:

	/* initialize stack */
	la	sp, _stack_top

	/* jump to program entry */
	jal	_start

	/* stop */
	jal	_stop
