	.text
	.globl	_start
_start:
	mv	s0, ra

	/* Run main() */
	li	a0, 0
	la	a1, 0
	jal	main

	mv	ra, s0
	jr	ra
