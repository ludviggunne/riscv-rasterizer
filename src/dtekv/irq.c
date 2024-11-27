#include <stddef.h>
#include <perf.h>
#include <timer.h>
#include <uart.h>

void interrupt(int mcause)
{
	uart_printf("interrupt received\n");
	switch (mcause)
	{
	case 18:
		print_all_profile_window_info(NULL);
		break;
	case MCAUSE_TIMER:
		timer_clear_interrupt();
		break;
	default:
		break;
	}
}
