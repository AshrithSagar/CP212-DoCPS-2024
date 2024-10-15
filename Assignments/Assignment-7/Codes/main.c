/* Application layer for the display module.
 * This will display a checkerboard pattern on the LED matrix.
 */
#include "display.h"

#define NUM_PICS 5
char pics[NUM_PICS][N][N] = {
    {{1, 1, 1, 1, 1},
     {1, 0, 0, 0, 1},
     {1, 0, 1, 0, 1},
     {1, 0, 0, 0, 1},
     {1, 1, 1, 1, 1}},

    {{0, 0, 1, 0, 0},
     {0, 1, 1, 1, 0},
     {1, 1, 1, 1, 1},
     {0, 1, 1, 1, 0},
     {0, 0, 1, 0, 0}},

    {{1, 0, 1, 0, 1},
     {0, 1, 0, 1, 0},
     {1, 0, 1, 0, 1},
     {0, 1, 0, 1, 0},
     {1, 0, 1, 0, 1}},

    {{0, 1, 0, 1, 0},
     {1, 0, 1, 0, 1},
     {0, 1, 1, 1, 0},
     {1, 0, 1, 0, 1},
     {0, 1, 0, 1, 0}},

    {{1, 0, 0, 0, 1},
     {0, 1, 0, 1, 0},
     {0, 0, 1, 0, 0},
     {0, 1, 0, 1, 0},
     {1, 0, 0, 0, 1}},
};

int main(void) {
  displayInit();

  int currentPic;
  currentPic = 0;

  while (1) {
    displayImage(pics[currentPic]);
    currentPic = (currentPic + 1) % NUM_PICS;
    naiveDelay(1000);
  }

  return 0;
}
