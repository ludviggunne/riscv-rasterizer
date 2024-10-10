#include <avr/io.h>
#include <util/delay.h>
#include "pif.h"

#define CTRL_PIN  2
#define DTEK_CLK  3
#define DTEK_DATA 4

void send(uint8_t *data)
{
	for (int i = 0; i < 4; i++)
	{
		uint8_t v = data[3 - i];
		if (v & 1)
		{
			PORTB |= _BV(DTEK_DATA);
		}
		else
		{
			PORTB &= ~_BV(DTEK_DATA);
		}

		PORTB |= _BV(DTEK_CLK);
		_delay_ms(1);

		PORTB &= ~_BV(DTEK_CLK);
		_delay_ms(1);

		v >>= 1;
	}
}

int main(int argc, char **argv)
{
	(void)argc;
	(void)argv;

	uint8_t recvbuf[4], sendbuf[4];

	// configure pins
	DDRB |= _BV(DTEK_CLK);
	DDRB |= _BV(DTEK_DATA);
	PORTB &= ~_BV(DTEK_CLK);
	PORTB &= ~_BV(DTEK_DATA);

	pif_host_transmit(CTRL_PIN, 0, 0, 0, 0);
}
