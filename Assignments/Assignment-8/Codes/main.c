/* Application layer for the display module.
 * Display an image, while using the SysTick timer
 */
#include "display.h"

// Lightning bolt
const char pic[N][N] = {{0, 0, 1, 0, 0},
                        {0, 1, 1, 0, 0},
                        {1, 1, 1, 1, 1},
                        {1, 0, 1, 1, 0},
                        {0, 0, 1, 0, 0}};

int main(void) {
  displayInit();
  displayImage(pic);

  while (1)
    ;

  return 0;
}
