#include <display.h>
#include <model.h>
#include <qmath.h>
#include <rast.h>
#include <uart.h>
#include <ctrl.h>
#include <perf.h>
#include <timer.h>

extern void *volatile		VGA_FRONT;
extern void *volatile		VGA_BACK;
extern volatile unsigned	VGA_RES;
extern volatile unsigned	VGA_STATUS;
extern unsigned char		VGA_MEM[2][WIDTH * HEIGHT];

static int			frame_count;
static unsigned char		(*cb)[WIDTH * HEIGHT];
static qval_t			zb[WIDTH * HEIGHT];

static void display_func(void)
{
	PROFILE_WINDOW_START(draw_frame);

	for (int i = 0; i < sizeof(*cb) / sizeof*(*cb); i += 4)
	{
		__asm__ ("sw zero, %0;" : "=m"(*(int *)&(*cb)[i]));
	}

	for (int i = 0; i < sizeof(zb) / sizeof*(zb); i++)
	{
		zb[i] = QMAX;
	}

	draw_model(g_model, &g_model_xfm, *cb, zb);

	PROFILE_WINDOW_END(draw_frame)

	{
		int sw = *(volatile int *) 0x04000010;

		if (sw & (1 << 0))
		{
			g_model_xfm.y = qadd(g_model_xfm.y, QVAL(-0.02));
		}
		if (sw & (1 << 1))
		{
			g_model_xfm.y = qadd(g_model_xfm.y, QVAL( 0.02));
		}
		if (sw & (1 << 2))
		{
			g_model_xfm.p = qadd(g_model_xfm.p, QVAL( 0.02));
		}
		if (sw & (1 << 3))
		{
			g_model_xfm.p = qadd(g_model_xfm.p, QVAL(-0.02));
		}
		if (sw & (1 << 4))
		{
			g_model_xfm.r = qadd(g_model_xfm.r, QVAL( 0.02));
		}
		if (sw & (1 << 5))
		{
			g_model_xfm.r = qadd(g_model_xfm.r, QVAL(-0.02));
		}
		if (sw & (1 << 6))
		{
			g_model_xfm.s = qadd(g_model_xfm.s, QVAL( 0.01));
		}
		if (sw & (1 << 7))
		{
			g_model_xfm.s = qadd(g_model_xfm.s, QVAL(-0.01));
		}
	}

	{
		while (VGA_STATUS & 1)
		{
		}

		VGA_BACK = cb;
		VGA_FRONT = cb;

		cb = &VGA_MEM[frame_count++ & 1];
	}
}

static void rast_main(int argc, char *argv[])
{
	cb = &VGA_MEM[1];

	for (;;)
	{
		display_func();
	}
}


int main(int argc, char *argv[])
{
	clear_counters();
	uart_init();
	ctrl_init();
	timer_init();
	clear_counters();

	timer_start(1000);
	rast_main(argc, argv);
}
