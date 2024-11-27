/*
 * By: Ludvig Gunne Lindström
 * Last modified: 2024-09-17
 */

#ifndef UART_H
#define UART_H

/* Functions for printing over UART. */

/*
 * Initialize UART.
 */
void uart_init(void);

/*
 * Write a character to UART.
 */
void uart_putc(char c);

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
