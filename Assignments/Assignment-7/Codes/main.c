/* Application layer for the display module.
 * This will display a checkerboard pattern on the LED matrix.
 */
#include "display.h"

#define NUM_PICS 5
char pic[N][N] = {{0, 1, 0, 1, 0},
                  {1, 0, 1, 0, 1},
                  {0, 1, 0, 1, 0},
                  {1, 0, 1, 0, 1},
                  {0, 1, 0, 1, 0}};

int main(void) {
  displayInit();

  while (1)
    displayImage(pic);

  return 0;
}
