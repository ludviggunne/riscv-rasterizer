#include <perf.h>
#include <display.h>
#include <ctrl.h>
#include <uart.h>
#include <timer.h>

void interrupt(int mcause)
{
	uart_printf("interrupt received\n");
	switch (mcause)
	{
	case 18:
		ctrl_recv();
		break;
	case MCAUSE_TIMER:
		timer_clear_interrupt();
		dump_perf_info();
		break;
	default:
		break;
	}
}
