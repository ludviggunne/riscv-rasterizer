#include <display.h>
#include <ctrl.h>
#include <uart.h>

void interrupt(int mcause)
{
	uart_printf("interrupt received\n");
	switch (mcause)
	{
	case 18:
		ctrl_recv();
		break;
	default:
		break;
	}
}
