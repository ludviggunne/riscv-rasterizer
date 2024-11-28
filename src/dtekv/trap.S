	.text
	.globl	_trap
_trap:
	/* save context */
	csrw	mscratch, s0
	la	s0, _trap_ctxt
	sw	x1, 0(s0)
	sw	x2, 4(s0)
	sw	x3, 8(s0)
	sw	x4, 12(s0)
	sw	x5, 16(s0)
	sw	x6, 20(s0)
	sw	x7, 24(s0)
	sw	x9, 28(s0)
	sw	x10, 32(s0)
	sw	x11, 36(s0)
	sw	x12, 40(s0)
	sw	x13, 44(s0)
	sw	x14, 48(s0)
	sw	x15, 52(s0)
	sw	x16, 56(s0)
	sw	x17, 60(s0)
	sw	x18, 64(s0)
	sw	x19, 68(s0)
	sw	x20, 72(s0)
	sw	x21, 76(s0)
	sw	x22, 80(s0)
	sw	x23, 84(s0)
	sw	x24, 88(s0)
	sw	x25, 92(s0)
	sw	x26, 96(s0)
	sw	x27, 100(s0)
	sw	x28, 104(s0)
	sw	x29, 108(s0)
	sw	x30, 112(s0)
	sw	x31, 116(s0)

	/* initialize stack */
	la	sp, _trap_stack_top

	/* check cause */
	csrr	a0, mcause
	bltz	a0, _interrupt

	/* handle exception (currently ignore) */
	csrr	t0, mepc
	addi	t0, t0, 4
	csrw	mepc, t0
	j	_trap_exit

_interrupt:
	/* handle interrupt */
	slli	t0, a0, 2
	andi	t0, t0, 0x7F
	la	t1, __irq_tbl
	add	t0, t1, t0
	lw	t0, 0(t0)
	beq	t0, zero, _trap_exit
	jalr	t0

_trap_exit:
	/* load context */
	lw	x1, 0(s0)
	lw	x2, 4(s0)
	lw	x3, 8(s0)
	lw	x4, 12(s0)
	lw	x5, 16(s0)
	lw	x6, 20(s0)
	lw	x7, 24(s0)
	lw	x9, 28(s0)
	lw	x10, 32(s0)
	lw	x11, 36(s0)
	lw	x12, 40(s0)
	lw	x13, 44(s0)
	lw	x14, 48(s0)
	lw	x15, 52(s0)
	lw	x16, 56(s0)
	lw	x17, 60(s0)
	lw	x18, 64(s0)
	lw	x19, 68(s0)
	lw	x20, 72(s0)
	lw	x21, 76(s0)
	lw	x22, 80(s0)
	lw	x23, 84(s0)
	lw	x24, 88(s0)
	lw	x25, 92(s0)
	lw	x26, 96(s0)
	lw	x27, 100(s0)
	lw	x28, 104(s0)
	lw	x29, 108(s0)
	lw	x30, 112(s0)
	lw	x31, 116(s0)
	csrr	s0, mscratch

	/* return from trap */
	mret

	.bss
_trap_ctxt:
	.fill	0x80

_trap_stack:
	.fill	0x1000
_trap_stack_top:

	.globl	__irq_tbl
__irq_tbl:
	.fill	0x80
