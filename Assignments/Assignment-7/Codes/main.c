/* Application layer for the display module.
 * This will display a checkerboard pattern on the LED matrix.
 */
#include "button.h"
#include "display.h"

#define NUM_PICS 3
char pics[NUM_PICS][N][N] = {
    // Blank
    {
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
    },
    // Left arrow
    {
        {0, 0, 1, 0, 0},
        {0, 1, 1, 1, 0},
        {1, 1, 1, 1, 1},
        {0, 1, 1, 1, 0},
        {0, 0, 1, 0, 0},
    },
    // Right arrow
    {
        {0, 0, 1, 0, 0},
        {0, 0, 1, 1, 1},
        {1, 1, 1, 1, 1},
        {0, 0, 1, 1, 1},
        {0, 0, 1, 0, 0},
    },
};

int main(void) {
  int currentPic;

  displayInit();
  buttonInit();

  while (1) {
    if (BUTTON_PRESSED(BTN_A)) {
      currentPic = 1;
      naiveDelay(100); // Debounce
    } else if (BUTTON_PRESSED(BTN_B)) {
      currentPic = 2;
      naiveDelay(100); // Debounce
    } else {
      currentPic = 0;
    }
    displayImage(pics[currentPic]);
  }

  return 0;
}
