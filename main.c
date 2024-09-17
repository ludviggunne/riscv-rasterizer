#include "display.h"
#include "qmath.h"
#include "uart.h"

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
}
