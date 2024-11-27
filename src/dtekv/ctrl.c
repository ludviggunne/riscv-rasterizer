#include <ctrl.h>
#include <gpio_io.h>
#include <model.h>
#include <uart.h>

#define BIT(x) (1 << x)

void ctrl_init(void)
{
	GPIO1_DIRECTION &= ~(BIT(CLKPIN) | BIT(DATAPIN)); /* set pins as inputs */
	GPIO1_INTERRUPTMASK |= BIT(CLKPIN); /* enable interrupts for clock pin */
}

void ctrl_recv(void)
{
	unsigned int data;

	uart_printf("receiving controller data...\n");

	data = 0;
	for (int i = 0; i < 32; i++)
	{
		while (!(GPIO1_DATA & BIT(CLKPIN)));
		data |= !!(GPIO1_DATA & BIT(DATAPIN));
		while ((GPIO1_DATA & BIT(CLKPIN)));
		data <<= 1;
	}

	unsigned char ux = (data >> 8) & 0xff;
	unsigned char uy = data & 0xff;
	char x = *(char*)&ux;
	char y = *(char*)&uy;

	qval_t qx = QINT(x);
	qval_t qy = QINT(y);

	g_model_xfm.y += TRANSFORM_SPEED * qx;
	g_model_xfm.p += TRANSFORM_SPEED * qy;

	uart_printf("joystick: [ %q, %q ]\n", qx, qy);

	/* clear interrupt */
	GPIO1_EDGECAPTURE = 0;
}


