/* By: Ludvig Gunne Lindström */

#include <stdarg.h>
#include <stddef.h>
#ifndef __riscv
#include <stdio.h>
#endif
#include <qmath.h>
#ifdef __riscv
#include <uart_io.h>
#endif

static const char hex[] = "0123456789abcdef";

void uart_putc(char c)
{
	c &= 127;
#ifdef __riscv
	/* wait for FIFO to be available */
	while (!(UART_CONTROL & 0xffff0000));
	/* write */
	UART_DATA = (UART_DATA & ~0xff) | c;
#else
	fputc(c, stdout);
#endif
}

void uart_puts(const char *s)
{
	for (; *s; s++)
	{
		uart_putc(*s);
	}
}

void uart_printf(const char *fmt, ...)
{
	char buf[32];
	size_t buflen;

	va_list args;
	va_start(args, fmt);

	/* Process format string */
	for (; *fmt; fmt++)
	{
		buflen = 0;
		char c = *fmt;
		switch (c)
		{
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
			case 'u':
			{
				unsigned int x = va_arg(args, unsigned int);
				if (x == 0)
				{
					uart_putc('0');
					continue;
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
			case 'l':
			{
				fmt++;
				c = *fmt;
				switch (c)
				{
				case 0:
					return;
				case 'd':
				{
					long long int x = va_arg(args, long long int);
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
				case 'u':
				{
					unsigned long long int x = va_arg(args, unsigned long long int);
					if (x == 0)
					{
						uart_putc('0');
						continue;
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
				default:
					break;
				}
				break;
			}
			case 'p':
			{
				void *p = va_arg(args, void*);
				if (p == 0)
				{
					uart_puts("NULL");
					continue;
				}
				uart_puts("0x");
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
				(void) qsnprint(q, buf, sizeof(buf));
				uart_puts(buf);
				break;
			}
			case 's':
			{
				const char *s = va_arg(args, const char *);
				uart_puts(s);
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
