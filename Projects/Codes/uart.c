#include "uart.h"
#include "nrf52833.h"

#define UART_TX_PIN 6
#define UART_RX_PIN 40
// Incorrect the manual, which interchanges these

void uart_init() {
  // Make pin connection
  NRF_UART0->PSEL.TXD = UART_TX_PIN;
  NRF_UART0->PSEL.RXD = UART_RX_PIN;

  NRF_UART0->BAUDRATE = 0x01D7E000;
  // BAUD rate; 115200; => 11520 bytes per second
  // Comprises of 1 start bit + 8 data bits + 1 stop bit

  NRF_UART0->TASKS_STARTTX = 1;
  NRF_UART0->TASKS_STARTRX = 1;
  NRF_UART0->ENABLE = 4;
  return;
}

char uart_putc(char ch) {
  // Set character to be transmitted
  NRF_UART0->TXD = ch;

  // Wait till TXDRDY is 1
  while (NRF_UART0->EVENTS_TXDRDY == 0)
    ;

  // Clear TXDRDY
  NRF_UART0->EVENTS_TXDRDY = 0;

  return ch;
}

char uart_getc(void) {
  // Wait till RXDRDY is 1
  while (NRF_UART0->EVENTS_RXDRDY == 0)
    ;

  // Clear RXDRDY
  NRF_UART0->EVENTS_RXDRDY = 0;

  // Return received character
  return NRF_UART0->RXD;
}

char *uart_fgets(char *buf, int bufsize) {
  /* Read a line from the UART
   * buf: buffer to store the line
   * bufsize: size of the buffer
   * return: pointer to the buffer
   */

  int i = 0;
  char c;
  for (i = 0; i < bufsize - 1; i++) {
    c = uart_getc();
    if (c == '\n' || c == '\r')
      break;
    buf[i] = c;
  }
  buf[i] = '\0';

  // Clear any leftover characters in the UART buffer
  while (NRF_UART0->EVENTS_RXDRDY == 1) {
    uart_getc();
  }

  return buf;
}
