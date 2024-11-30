#include "printlib.h"
#include "radio.h"
#include "uart.h"

void rx_callback(const char buf[], unsigned int n) {
  // Print
  myputchar(buf[0]);
}

void setup() {
  uart_init();
  radio_init(rx_callback);
}

void loop(void) {
  char c;
  while (1) {
    c = uart_getc();
    radio_send(&c, 1);
  }
}
