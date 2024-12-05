/* By: Ludvig Gunne Lindström */
	.text
	.globl	_stop
_stop:
	csrc	mstatus, 3	/* mie */
_hlt:
	j	_hlt
