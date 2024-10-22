/* Device abstraction layer implementing the
 * display driver for the LED matrix
 */
#include "display.h"

#define CLOCK_CYCLES_PER_MS 64000

// LED matrix pins
const int LED_ROW_PINS[N] = {21, 22, 15, 24, 19};
const int LED_COL_PINS[N] = {28, 11, 31, 37, 30};

void displayInit(void) {
  /*
   * Initialize the LED matrix with a blank display
   * Set the row pins as OUTPUT and LOW
   * Set the column pins as OUTPUT and HIGH
   */

  int i;
  for (i = 0; i < N; i++) {
    digitalWrite(LED_ROW_PINS[i], LOW);
    pinMode(LED_ROW_PINS[i], OUTPUT);

    digitalWrite(LED_COL_PINS[i], HIGH);
    pinMode(LED_COL_PINS[i], OUTPUT);
  }

  return;
}

void displayImage(const char image[N][N]) {
  /*
   * Display an image on the LED matrix
   * image: 2D array of 1s (LED ON) and 0s (LED OFF)
   * The image is displayed row by row.
   */

  int r, c;
  for (r = 0; r < N; r++) {
    // Turn ON the row
    digitalWrite(LED_ROW_PINS[r], HIGH);

    // Selectively turn ON the columns
    for (c = 0; c < N; c++) {
      if (image[r][c] == 1)
        digitalWrite(LED_COL_PINS[c], LOW);
    }

    timerDelay(3);
    // 3 ms * 5 rows => 15 ms/frame => ~66.66 fps

    // Turn OFF all the columns
    for (c = 0; c < N; c++) {
      digitalWrite(LED_COL_PINS[c], HIGH);
    }

    // Turn OFF the row
    digitalWrite(LED_ROW_PINS[r], LOW);
  }

  return;
}

int row;
void displayRefresh(void) {
  digitalWrite(LED_ROW_PINS[row], 0); // Turn off the previous row
  row = (row + 1) % N;
  for (int c = 0; c < N; c++) {
    digitalWrite(LED_COL_PINS[c], 1);
  }
}
