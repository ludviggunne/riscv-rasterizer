	.text
	.globl	_trap
_trap:
	csrrw	s0, mscratch, s0
	la	s0, _trap_ctxt

	sw	t0, 0(s0)
	sw	t1, 4(s0)

#if 1
	la	t0, 0x04000000
	lw	t1, 0(t0)
	addi	t1, t1, 1
	sw	t1, 0(t0)
	li	t1, -1
	sw	t1, 0xdc(t0)
#endif

	lw	t0, 0(s0)
	lw	t1, 4(s0)

	csrrw	s0, mscratch, s0
	
	mret

	.bss
_trap_ctxt:
	.fill	0x80

