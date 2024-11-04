#include "uart.h"

#define IOREG(addr) (*((volatile long *)(addr)))

#define UART_TX_PIN 6
#define UART_RX_PIN 40
// Incorrect the manual, which interchanges these

#define UART_STARTTX IOREG(0x40002008)
#define UART_STARTRX IOREG(0x40002000)
#define UART_TXDRDY IOREG(0x4000211C)
#define UART_RXDRDY IOREG(0x40002108)
#define UART_ENABLE IOREG(0x40002500)
#define UART_PSEL_TXD IOREG(0x4000250C)
#define UART_PSEL_RXD IOREG(0x40002514)
#define UART_TXD IOREG(0x4000251C)
#define UART_RXD IOREG(0x40002518)
#define UART_BAUDRATE IOREG(0x40002524)

void uart_init() {
  // Make pin connection
  UART_PSEL_TXD = UART_TX_PIN;
  UART_PSEL_RXD = UART_RX_PIN;

  // Set BAUD rate; 115200;
  // => 11520 bytes per second, including 1 start bit + 8 data bits + 1 stop bit
  UART_BAUDRATE = 0x01D7E000;

  // Start TX; Trigger task;
  UART_STARTTX = 1;

  // Start RX; Trigger task;
  UART_STARTRX = 1;

  // Enable UART
  UART_ENABLE = 4;

  return;
}

void uart_putc(char ch) {
  // Set character to be transmitted
  UART_TXD = ch;

  // Wait till TXDRDY is 1
  while (UART_TXDRDY == 0)
    ;

  // Clear TXDRDY
  UART_TXDRDY = 0;

  return;
}

char uart_getc(void) {
  // Wait till RXDRDY is 1
  while (UART_RXDRDY == 0)
    ;

  // Clear RXDRDY
  UART_RXDRDY = 0;

  // Return received character
  return UART_RXD;
}

char *uart_fgets(char *buf, int bufsize) {
  int i = 0;
  while (i < bufsize - 1) {
    int c = uart_getc();
    if (c == '\n' || c == '\r') {
      break;
    }
    buf[i++] = c;
  }
  buf[i] = '\0';
  return buf;
}
