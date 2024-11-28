#include <button_io.h>
#include <perf_json.h>
#include <timer.h>
#include <timer_io.h>
#include <uart.h>

void interrupt(int mcause)
{
	switch (mcause)
	{
	case BUTTON_IRQ:
		if (BUTTON_DATA & 1)
		{
			print_all_profile_windows_json();
		}
		BUTTON_EDGECAPTURE = 0;
		break;
	case TIMER_IRQ:
		timer_clr_int();
		break;
	default:
		break;
	}
}