	.section	.mvec, "ax", @progbits

_tvec:
	j	_trap

_rvec:
	j	_reset
