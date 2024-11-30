#include "printlib.h"
#include "radio.h"
#include "uart.h"

void rx_callback(const char buf[], unsigned int n) {
  // Print
  myprintf(">> %s\n", buf);
}

void setupReceiver() {
  uart_init();
  myprintf("\nTrying to receive\n");
  radio_init(rx_callback);
}

void setupSender() {
  uart_init();
  myprintf("\nEnter something to send: ");
  char c = uart_getc();
  myprintf("\nSending %c\n", c);
  radio_send(&c, 1);
  myprintf("Sent\n");
}

void loop(void) {
  while (1)
    ;
}
