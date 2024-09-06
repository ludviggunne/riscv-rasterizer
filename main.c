#include "display.h"
#include "qmath.h"

static void display_qval(qval_t v)
{
	char s[6];
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

int main()
{
#if 1
	/* enable button interrupt */
	*(volatile int *)0x040000d8 = -1;
	/* enable button edge trigger */
	*(volatile int *)0x040000dc = -1;
#endif

	{
		qval_t v = qsqrt(QVAL(2));

		display_qval(v);
	}
}
