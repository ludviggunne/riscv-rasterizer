/* By: Ludvig Gunne Lindström */
#ifndef UART_H
#define UART_H

/*
 * Functions for printing over UART.
 */

/*
 * Write a character to UART.
 */
void uart_putc(char c);

/*
 * Write a string to UART.
 */
void uart_puts(const char *s);

/*
 * Print formatted string to UART.
 * Supported format specifiers:
 * %d   - int
 * %u   - unsigned int
 * %ld  - long long int
 * %lu  - unsigned long long int
 * %p   - address
 * %q   - qval_t
 */
void uart_printf(const char *fmt, ...);

#endif /* UART_H */
