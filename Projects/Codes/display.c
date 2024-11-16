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
    pinMode(LED_ROW_PINS[i], OUTPUT, INPUT);

    digitalWrite(LED_COL_PINS[i], HIGH);
    pinMode(LED_COL_PINS[i], OUTPUT, INPUT);
  }

  timerInterruptEnable(3);
  // 3 ms * 5 rows => 15 ms/frame => ~66.66 fps

  return;
}

int frameBuffer[N][N];
void displayImage(int image[N][N]) {
  /*
   * Wrapper to display an image on the LED matrix
   * image: 2D array of 1s (LED ON) and 0s (LED OFF)
   * Copy to a frame buffer and periodically
   * call display refresh by timer interrupts
   */

  int r, c;
  for (r = 0; r < N; r++) {
    for (c = 0; c < N; c++) {
      frameBuffer[r][c] = image[r][c];
    }
  }
}

int row;
void displayRefresh(void) {
  /*
   * Display the image from the frame buffer
   * The image is displayed row by row
   */

  // Turn off the previous row
  digitalWrite(LED_ROW_PINS[row], LOW);

  row = (row + 1) % N; // Update the row

  // Turn ON the updated row
  digitalWrite(LED_ROW_PINS[row], HIGH);

  int c;
  // Turn ON/OFF the columns accordingly
  for (c = 0; c < N; c++)
    if (frameBuffer[row][c] == 1)
      digitalWrite(LED_COL_PINS[c], LOW);
    else if (frameBuffer[row][c] == 0)
      digitalWrite(LED_COL_PINS[c], HIGH);

  return;
}

void SysTick_Handler(void) {
  displayRefresh(); // Called periodically
}
