#include <display.h>
#include <model.h>
#include <qmath.h>
#include <rast.h>
#include <uart.h>

static void display_qval(qval_t v)
{
	char s[8];
	int p = 0;

	qsnprint(v, s, sizeof(s));

	for (int i = 0; i < 6; i++)
	{
		if (s[p] == '\0')
		{
			display_char(i, ' ');
		}
		else if (s[p + 1] == '.')
		{
			display_char(i, s[p] | 0x80);
			p = p + 2;
		}
		else
		{
			display_char(i, s[p]);
			p = p + 1;
		}
	}
}

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
	for (int i = 0; i < sizeof(*cb) / sizeof*(*cb); i += 4)
	{
		__asm__ ("sw zero, %0;" : "=m"(*(int *)&(*cb)[i]));
	}

	for (int i = 0; i < sizeof(zb) / sizeof*(zb); i++)
	{
		zb[i] = QMAX;
	}

	draw_model(g_model, &g_model_xfm, *cb, zb);

	g_model_xfm.y = qadd(g_model_xfm.y, QVAL( 0.02));
	g_model_xfm.p = qadd(g_model_xfm.p, QVAL( 0.02));

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
#if 1
	/* enable button interrupt */
	*(volatile int *)0x040000d8 = -1;
	/* enable button edge trigger */
	*(volatile int *)0x040000dc = -1;
#endif

	uart_init();
	uart_printf("hello, the number forty-three is %d!\n", 43);
	uart_printf("main is at %p, in case you were wondering.\nargc is %d.\n", main, argc);
	uart_printf("QPI is %q, and thats %s.\n", QPI, "pretty good");
	uart_printf("this is a backslash: \\, and this is a precent sign: %%.\n");

	{
		qval_t f = QVAL(1);
		qval_t v = QVAL(0);

		for (int i = 1; i <= 10; i++)
		{
			v = qadd(v, qdiv(QVAL(1), f));
			f = qmul(f, QINT(i));
		}

		display_qval(v);
	}

	rast_main(argc, argv);
}
