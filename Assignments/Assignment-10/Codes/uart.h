#ifndef UART_H
#define UART_H

#ifndef STDARG_H
#define STDARG_H
#include <stdarg.h>
#endif // STDARG_H

void uart_init(void);
void uart_putc(char ch);

#endif // UART_H
