#include <stdint.h>
#include <stdio.h>
#include <avr/io.h>
#include <util/setbaud.h>
#include <util/delay.h>
#include <string.h>
#include <joybus.h>

#define CTRL_PIN	2 /* pin 2 on arduino */
#define DTEK_CLK	3 /* pin 11 on arduino */
#define DTEK_DATA	4 /* pin 12 on arduino */
#define LED		5

#define RESET		0xff
#define POLL		0x01

#define THRESHOLD	2

#define ABS(x)		((x) < 0 ? -(x) : (x))

/* determine if the controller inputs has changed */
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

/* send controller data to dtekv board */
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

int usart_putc(char c, FILE *f)
{
	(void)f;
	while (!(UCSR0A & _BV(UDRE0)))
		;

	UDR0 = c;
	return 0;
}

void usart_init(void)
{
	UBRR0L = UBRRL_VALUE;
	UBRR0H = UBRRH_VALUE;
	/* enable transmission */
	UCSR0B = _BV(TXEN0);
	/* 8 data bits, 1 stop bit */
	UCSR0C = _BV(UCSZ01) | _BV(UCSZ00);
	/* setup stream */
	stdout = fdevopen(usart_putc, NULL);
}

int main(void)
{
	usart_init();
	printf("USART initialized\n");

	uint8_t recvbuf[4];
	uint8_t recvbuf_prev[4] = { 0 };

	/* configure pins */
	DDRB |= _BV(DTEK_CLK);
	DDRB |= _BV(DTEK_DATA);
	PORTB &= ~_BV(DTEK_CLK);
	PORTB &= ~_BV(DTEK_DATA);

	/* reset controller */
	uint8_t request = RESET;
	joybus_host_transceive(CTRL_PIN, &request, 1, recvbuf, 3);
	printf("reset done\n");

	for (;;)
	{
		request = POLL;
		joybus_host_transceive(CTRL_PIN, &request, 1, recvbuf, 4);
		if (changed(recvbuf, recvbuf_prev)) {
			printf("joystick: [ %d, %d ]\n", *(int8_t*)&recvbuf[2], *(int8_t*)&recvbuf[3]);
			send(recvbuf);
		}
		_delay_ms(33);
		memcpy(recvbuf_prev, recvbuf, sizeof(*recvbuf));
	}
}
