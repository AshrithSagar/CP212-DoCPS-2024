#ifndef UART_H
#define UART_H

void uart_init(void);
char uart_putc(char ch);
char uart_getc(void);
char *uart_fgets(char *buf, int bufsize);

#endif // UART_H
