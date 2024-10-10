#include <display.h>
#include <ctrl.h>

void interrupt(int mcause)
{
	switch (mcause)
	{
	case 18:
		ctrl_recv();
		break;
	default:
		break;
	}
}
