#include "display.h"
#include "printlib.h"
#include "uart.h"

// Lightning bolt
const char pic[N][N] = {{0, 0, 1, 0, 0},
                        {0, 1, 1, 0, 0},
                        {1, 1, 1, 1, 1},
                        {1, 0, 1, 1, 0},
                        {0, 0, 1, 0, 0}};

int main(void) {
  uart_init();
  displayInit();
  displayImage(pic);

  myprintf("%c", 'A');
  myprintf("%c", '\n');

  return 0;
}
