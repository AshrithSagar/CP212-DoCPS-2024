/**
 * @file uart.c
 * @brief UART driver implementation for nRF52833 microcontroller.
 *
 * This file contains the implementation of UART initialization and basic
 * UART communication functions for the nRF52833 microcontroller.
 */

#include "uart.h"
#include "nrf52833.h"

/**
 * @brief Initialize the UART peripheral.
 *
 * This function configures the UART peripheral with the specified TX and RX
 * pins, sets the baud rate to 115200, and enables the UART transmitter and
 * receiver.
 */
void uart_init();

/**
 * @brief Transmit a character over UART.
 *
 * This function transmits a single character over UART and waits until the
 * transmission is complete.
 *
 * @param ch The character to be transmitted.
 * @return The transmitted character.
 */
char uart_putc(char ch);

/**
 * @brief Receive a character over UART.
 *
 * This function waits for a character to be received over UART and returns
 * the received character.
 *
 * @return The received character.
 */
char uart_getc(void);

/**
 * @brief Read a line from the UART.
 *
 * This function reads a line of characters from the UART until a newline or
 * carriage return character is encountered or the buffer is full. The line
 * is stored in the provided buffer.
 *
 * @param buf The buffer to store the line.
 * @param bufsize The size of the buffer.
 * @return Pointer to the buffer containing the line.
 */
char *uart_fgets(char *buf, int bufsize);

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
