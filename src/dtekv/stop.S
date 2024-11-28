	.text
	.globl	_stop
_stop:
	csrc	mstatus, 3
_hlt:
	j	_hlt
