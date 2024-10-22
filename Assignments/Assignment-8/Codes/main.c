/* Application layer for the display module.
 * Display left arrow as long as the left button is pressed
 * and right arrow as long as the right button is pressed.
 */
#include "display.h"

#define NUM_PICS 3
const char pics[NUM_PICS][N][N] = {
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
        {0, 1, 0, 0, 0},
        {1, 1, 1, 1, 1},
        {0, 1, 0, 0, 0},
        {0, 0, 1, 0, 0},
    },
    // Right arrow
    {
        {0, 0, 1, 0, 0},
        {0, 0, 0, 1, 0},
        {1, 1, 1, 1, 1},
        {0, 0, 0, 1, 0},
        {0, 0, 1, 0, 0},
    },
};

int main(void) {
  displayInit();

  while (1) {
    displayImage(pics[0]);
  }

  return 0;
}
