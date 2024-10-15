/* Application layer for the display module.
 * This will display a checkerboard pattern on the LED matrix.
 */
#include "button.h"
#include "display.h"

#define NUM_PICS 5
char pics[NUM_PICS][N][N] = {
    {
        {0, 1, 0, 1, 0},
        {1, 0, 1, 0, 1},
        {0, 1, 0, 1, 0},
        {1, 0, 1, 0, 1},
        {0, 1, 0, 1, 0},
    },
    {
        {1, 0, 1, 0, 1},
        {0, 1, 0, 1, 0},
        {1, 0, 1, 0, 1},
        {0, 1, 0, 1, 0},
        {1, 0, 1, 0, 1},
    },
    {
        {0, 0, 0, 0, 0},
        {0, 1, 1, 1, 0},
        {0, 1, 1, 1, 0},
        {0, 1, 1, 1, 0},
        {0, 0, 0, 0, 0},
    },
    {
        {1, 1, 1, 1, 1},
        {1, 0, 0, 0, 1},
        {1, 0, 0, 0, 1},
        {1, 0, 0, 0, 1},
        {1, 1, 1, 1, 1},
    },
    {
        {0, 1, 0, 1, 0},
        {1, 0, 1, 0, 1},
        {0, 1, 0, 1, 0},
        {1, 0, 1, 0, 1},
        {0, 1, 0, 1, 0},
    },
};
int currentPic = 0;

int main(void) {
  displayInit();
  buttonInit();

  while (1) {
    displayImage(pics[currentPic]);

    if (BUTTON_PRESSED(BTN_A)) {
      // Change to the next image
      currentPic = (currentPic + 1) % NUM_PICS;
      naiveDelay(200); // Debounce delay
    }

    if (BUTTON_PRESSED(BTN_B)) {
      // Change to the previous image
      currentPic = (currentPic - 1 + NUM_PICS) % NUM_PICS;
      naiveDelay(200); // Debounce delay
    }
  }

  return 0;
}
