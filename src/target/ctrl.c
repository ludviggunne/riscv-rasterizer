#include <ctrl.h>
#include <model.h>
#include <stdint.h>

#define BIT(x) (1 << x)
#define GPIO_BASE ((volatile int*)0x040000e0)

void ctrl_init(void)
{
	*(GPIO_BASE + 1) &= ~(BIT(CLKPIN) | BIT(DATAPIN)); // set pins as inputs
	*(GPIO_BASE + 2) |= BIT(CLKPIN); // enable interrupts for clock pin
}

void ctrl_recv(void)
{
	uint32_t data;

	data = 0;
	for (int i = 0; i < 32; i++)
	{
		while (!(*GPIO_BASE & BIT(CLKPIN)));
		data |= !!(*GPIO_BASE & BIT(DATAPIN));
		while ((*GPIO_BASE & BIT(CLKPIN)));
		data <<= 1;
	}

	uint8_t ux = (data >> 8) & 0xff;
	uint8_t uy = data & 0xff;
	int8_t x = *(int8_t*)&ux;
	int8_t y = *(int8_t*)&uy;

	(void)x;
	(void)y;
}


