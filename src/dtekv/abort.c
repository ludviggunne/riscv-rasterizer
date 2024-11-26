_Noreturn void _stop(void);

void abort(void)
{
	_stop();
}
