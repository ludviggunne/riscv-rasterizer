/* By: Ludvig Gunne Lindström */
_Noreturn void _stop(void);

void abort(void)
{
	_stop();
}
