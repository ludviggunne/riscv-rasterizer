	.text
	.globl	_reset
_reset:
	/* enable interrupts */
	li	t1, -1
	csrw	mie, t1
	li	t0, (1 << 3)
	csrs	mstatus, t0

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

	/* initialize global pointer */
	la	gp, _gp

	/* jump to main */
	jal	_start

	/* stop */
	j	_stop
