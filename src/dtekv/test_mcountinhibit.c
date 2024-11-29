#ifndef TEST_MCOUNTINHIBIT_C
#define TEST_MCOUNTINHIBIT_C

#include <timer.h>
#include <io.h>
#include <uart.h>

static volatile int test_mcountinhibit_flag = 1;

static void test_mcountinhibit_timer_fn(void)
{
	unsigned int mcycle = csrr(mcycle);
	if (mcycle)
	{
		uart_printf("mcycle is %u. mcountinhibit is probably not implemented.\n", mcycle);
	}
	else
	{
		uart_printf("mcycle is 0. mcountinhibit is probably implemented.");
	}
	test_mcountinhibit_flag = 0;
}

void test_mcountinhibit(void)
{
	csrw(mcountinhibit, -1);
	csrw(mcycle, 0);
	timer_start(1000, test_mcountinhibit_timer_fn);
	while (test_mcountinhibit_flag);
	csrw(mcountinhibit, 0);
}

#endif
