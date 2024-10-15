/* Device abstraction layer implementing the
 * display driver for the LED matrix
 */
#include "display.h"

#define CLOCK_CYCLES_PER_MS 64000

// LED matrix pins
int LED_ROW_PINS[] = {21, 22, 15, 24, 19};
int LED_COL_PINS[] = {28, 11, 31, 37, 30};

void naiveDelay(int ms) {
  /*
   * Delay function using a busy loop
   * ms: delay in milliseconds
   * Note: Inefficient method. May block CPU cycles.
   */

  volatile int clocks = ms * CLOCK_CYCLES_PER_MS;
  // 64000 clock cycles in 1ms. 1 clock cycle is 1/64000 ms.

  while (clocks > 0) {
    clocks -= 10;
  }

  return;
}

void displayInit(void) {
  /*
   * Initialize the LED matrix with a blank display
   * Set the row pins as OUTPUT and LOW
   * Set the column pins as OUTPUT and HIGH
   */

  for (int i = 0; i < N; i++) {
    digitalWrite(LED_ROW_PINS[i], LOW);
    pinMode(LED_ROW_PINS[i], OUTPUT);

    digitalWrite(LED_COL_PINS[i], HIGH);
    pinMode(LED_COL_PINS[i], OUTPUT);
  }

  return;
}

void displayImage(char image[N][N]) {
  /*
   * Display an image on the LED matrix
   * image: 2D array of 1s (LED ON) and 0s (LED OFF)
   * The image is displayed row by row.
   */

  for (int r = 0; r < N; r++) {
    // Turn ON the row
    digitalWrite(LED_ROW_PINS[r], HIGH);

    // Selectively turn ON the columns
    for (int c = 0; c < N; c++) {
      if (image[r][c] == 1)
        digitalWrite(LED_COL_PINS[c], LOW);
    }

    naiveDelay(3);
    // 3 ms * 5 rows => 15 ms/frame => ~66.66 fps

    // Turn OFF all the columns
    for (int c = 0; c < N; c++) {
      digitalWrite(LED_COL_PINS[c], HIGH);
    }

    // Turn OFF the row
    digitalWrite(LED_ROW_PINS[r], LOW);
  }

  return;
}
