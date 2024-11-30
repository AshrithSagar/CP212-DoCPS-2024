#include "printlib.h"
#include "radio.h"
#include "uart.h"

void rx_callback(const char buf[], unsigned int n) {
  // Print
  myprintf(">> %s\n", buf);
}

void setup() {
  uart_init();

  myprintf("\nTrying to send\n");
  radio_send("G", 1);
  myprintf("Sent\n");
}
void loop(void) {}
