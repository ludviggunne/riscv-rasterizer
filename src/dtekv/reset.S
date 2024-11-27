	.text
	.globl	_reset
_reset:
	/* initialize global pointer */
	.option	push
	.option	norelax
	la	gp, __global_pointer$
	.option	pop

	/* enable interrupts */
	li	t1, 0xFFFFFFFF
	csrw	mie, t1
	csrs	mstatus, 3

	/* clear bss */
	la	t2, __bss_start
	la	t3, __bss_end
0:
	bge	t2, t3, 1f
	sw	zero, 0(t2)
	addi	t2, t2, 4
	beq	zero, zero, 0b
1:

	/* initialize stack */
	la	sp, _stack_top

	/* jump to program entry */
	jal	_start

	/* stop */
	jal	_stop
