#include <ctrl.h>
#include <model.h>
#include <uart.h>

#define BIT(x) (1 << x)
#define GPIO_BASE ((volatile int*)0x040000e0)

void ctrl_init(void)
{
	// *(GPIO_BASE + 1) &= ~(BIT(CLKPIN) | BIT(DATAPIN)); // set pins as inputs
	// *(GPIO_BASE + 2) |= BIT(CLKPIN); // enable interrupts for clock pin
	*(GPIO_BASE + 1) = 0;
	*(GPIO_BASE + 2) = 0xffffffff;
}

void ctrl_recv(void)
{
	unsigned int data;

	uart_printf("receiving controller data...\n");

	data = 0;
	for (int i = 0; i < 32; i++)
	{
		while (!(*GPIO_BASE & BIT(CLKPIN)));
		data |= !!(*GPIO_BASE & BIT(DATAPIN));
		while ((*GPIO_BASE & BIT(CLKPIN)));
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

	// clear interrupt
	*(GPIO_BASE + 3) = 0;
}


