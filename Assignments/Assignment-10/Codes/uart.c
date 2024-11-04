#include "uart.h"

#define IOREG(addr) (*((volatile long *)(addr)))

#define UART_TX_PIN 6
// Incorrect the manual, which says it as 40

#define UART_STARTTX IOREG(0x40002008)
#define UART_TXDRDY IOREG(0x4000211C)
#define UART_ENABLE IOREG(0x40002500)
#define UART_PSEL_TXD IOREG(0x4000250C)
#define UART_TXD IOREG(0x4000251C)
#define UART_BAUDRATE IOREG(0x40002524)

void uart_init() {
  // Make pin connection
  UART_PSEL_TXD = UART_TX_PIN;

  // Set BAUD rate; 115200;
  // => 11520 bytes per second, including 1 start bit + 8 data bits + 1 stop bit
  UART_BAUDRATE = 0x01D7E000;

  // Start TX; Trigger task;
  UART_STARTTX = 1;

  // Enable UART
  UART_ENABLE = 4;

  return;
}

void uart_putc(char ch) {
  // Set character to be transmitted
  UART_TXD = ch;

  // Wait till TXDRDY is 0
  while (UART_TXDRDY == 0)
    ;

  // Clear TXDRDY
  UART_TXDRDY = 0;

  return;
}
