#include "display.h"
#include "shell.h"
#include "uart.h"

int main(void) {
  uart_init();
  displayInit();
  shellInit();

  return 0;
}
