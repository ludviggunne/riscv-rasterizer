/*
 * By: Ludvig Gunne Lindström
 * Last modified: 2024-09-17
 */

#ifndef UART_H
#define UART_H

void uart_init(void);
void uart_putc(char c);

// Supported format specifiers:
// %d   - int
// %ull - uint64_t
// %p   - address
// %q   - qval_t
void uart_printf(const char *fmt, ...);

#endif /* UART_H */
