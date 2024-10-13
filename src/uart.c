/*
 * By: Ludvig Gunne Lindström
 * Last modified: 2024-09-17
 */

#include <stdarg.h>
#include <stddef.h>
#ifndef __riscv
#include <stdio.h>
#endif
#include <qmath.h>
#include <uart.h>

#define UART_DATA    ((volatile int *) 0x04000040)
#define UART_CONTROL ((volatile int *) 0x04000044)

static int is_init = 0;
static const char hex[] = "0123456789abcdef";

void uart_init(void)
{
	if (is_init) return;
#ifdef __riscv
	// // disable interrupts
	// *UART_CONTROL &= ~3;
#endif
	is_init = 1;
}

void uart_putc(char c)
{
	c &= 127;
#ifdef __riscv
	// wait for FIFO to be available
	while (!(*UART_CONTROL & 0xffff0000));
	// write
	*UART_DATA = (*UART_DATA & ~0xff) | c;
#else
	fputc(c, stdout);
#endif
}

void uart_printf(const char *fmt, ...)
{
	uart_init();
	char buf[32];
	size_t buflen;

	va_list args;
	va_start(args, fmt);

	for (; *fmt; fmt++)
	{
		buflen = 0;
		char c = *fmt;
		switch (c)
		{
		// case '\\':
		// 	fmt++;
		// 	switch (c)
		// 	{
		// 	case 0:
		// 		uart_putc('\\');
		// 		return;
		// 	case '\\':
		// 		uart_putc('\\');
		// 		break;
		// 	case 'n':
		// 		uart_putc('\n');
		// 		break;
		// 	case 't':
		// 		uart_putc('\t');
		// 		break;
		// 	case 'r':
		// 		uart_putc('\r');
		// 		break;
		// 	default:
		// 		uart_putc('\\');
		// 		uart_putc(c);
		// 		break;
		// 	}
		// 	break;
		case '%':
			fmt++;
			c = *fmt;
			switch (c)
			{
			case 0:
				return;
			case 'd':
			{
				int x = va_arg(args, int);
				if (x == 0)
				{
					uart_putc('0');
					continue;
				}
				if (x < 0)
				{
					uart_putc('-');
					x = -x;
				}
				while (x)
				{
					buf[buflen++] = '0' + x % 10;
					x /= 10;
				}
				for (int i = buflen - 1; i >= 0; i--)
				{
					uart_putc(buf[i]);
				}
				break;
			}
			case 'p':
			{
				void *p = va_arg(args, void*);
				if (p == 0)
				{
					uart_putc('N');
					uart_putc('U');
					uart_putc('L');
					uart_putc('L');
					continue;
				}
				uart_putc('0');
				uart_putc('x');;
				size_t i = sizeof(void*) * 8;
				do {
					i -= 4;
					size_t v = ((size_t) p >> i) & 15;
					uart_putc(hex[v]);
				} while (i);
				break;
			}
			case 'q':
			{
				qval_t q = va_arg(args, qval_t);
				buflen = qsnprint(q, buf, sizeof(buf));
				for (const char *ptr = buf; *ptr; ptr++)
				{
					uart_putc(*ptr);
				}
				break;
			}
			case 's':
			{
				const char *s = va_arg(args, const char *);
				for (; *s; s++)
				{
					uart_putc(*s);
				}
				break;
			}
			case '%':
				uart_putc('%');
				break;
			default:
				uart_putc(c);
				break;
			}
			break;
		default:
			uart_putc(c);
			break;
		}
	}
}
