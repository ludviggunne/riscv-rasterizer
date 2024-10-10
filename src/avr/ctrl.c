#include <stdint.h>
#include <avr/io.h>
#include <util/delay.h>
#include <string.h>
#include "pif.h"

#define CTRL_PIN  2
#define DTEK_CLK  3
#define DTEK_DATA 4
#define LED 5

#define RESET 0xff
#define POLL 0x01

#define THRESHOLD 2

#define ABS(x) ((x) < 0 ? -(x) : (x))

int changed(uint8_t *now, uint8_t *then)
{
	if (now[0] != then[0])
		return 1;
	if (now[1] != then[1])
		return 1;

	int8_t xnow = *(int8_t*)&now[2];
	int8_t ynow = *(int8_t*)&now[3];
	int8_t xthen = *(int8_t*)&then[2];
	int8_t ythen = *(int8_t*)&then[3];

	if (ABS(xnow - xthen) > THRESHOLD)
		return 1;
	if (ABS(ynow - ythen) > THRESHOLD)
		return 1;

	return 0;
}

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
		_delay_us(10);

		PORTB &= ~_BV(DTEK_CLK);
		_delay_us(10);

		v >>= 1;
	}
}

void blink(void)
{
	PORTB &= ~_BV(LED);
	DDRB |= _BV(LED);

	for (;;)
	{
		PORTB |= _BV(LED);
		_delay_ms(500);
		PORTB &= ~_BV(LED);
		_delay_ms(500);
	}
}

int main(void)
{
	blink();

	uint8_t recvbuf[4];
	uint8_t recvbuf_prev[4] = { 0 };

	// configure pins
	DDRB |= _BV(DTEK_CLK);
	DDRB |= _BV(DTEK_DATA);
	PORTB &= ~_BV(DTEK_CLK);
	PORTB &= ~_BV(DTEK_DATA);

	// reset controller
	uint8_t request = RESET;
	pif_host_transmit(CTRL_PIN, &request, 1, recvbuf, 3);

	for (;;)
	{
		request = POLL;
		pif_host_transmit(CTRL_PIN, &request, 1, recvbuf, 4);
		if (changed(recvbuf, recvbuf_prev))
			send(recvbuf);
		_delay_ms(33);
		memcpy(recvbuf_prev, recvbuf, sizeof(*recvbuf));
	}
}
