#ifndef UART_H
#define UART_H

#ifndef STDARG_H
#define STDARG_H
#include <stdarg.h>
#endif // STDARG_H

void uart_init(void);
void uart_putc(char ch);
char uart_getc(void);

#endif // UART_H
