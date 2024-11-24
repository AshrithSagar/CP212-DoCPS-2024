/* Device abstraction layer implementing the
 * display driver for the LED matrix
 */
#include "display.h"
#include "gpio.h"
#include "timer.h"

#define CLOCK_CYCLES_PER_MS 64000

typedef struct {
  int rowPins[N];
  int colPins[N];
  int frameBuffer[N][N];
  int currentRow;
} Display;

Display display = {
    .rowPins = {21, 22, 15, 24, 19},
    .colPins = {28, 11, 31, 37, 30},
    .currentRow = 0,
};

void displayInit(void) {
  /*
   * Initialize the LED matrix with a blank display
   * Set the row pins as OUTPUT and LOW
   * Set the column pins as OUTPUT and HIGH
   */

  for (int i = 0; i < N; i++) {
    digitalWrite(display.rowPins[i], LOW);
    pinMode(display.rowPins[i], OUTPUT, PULL_NONE);

    digitalWrite(display.colPins[i], HIGH);
    pinMode(display.colPins[i], OUTPUT, PULL_NONE);
  }

  timerInterruptEnable(3);
  // 3 ms * 5 rows => 15 ms/frame => ~66.66 fps
}

void displayImage(int image[N][N]) {
  /*
   * Wrapper to display an image on the LED matrix
   * image: 2D array of 1s (LED ON) and 0s (LED OFF)
   * Copy to a frame buffer and periodically
   * call display refresh by timer interrupts
   */

  for (int r = 0; r < N; r++) {
    for (int c = 0; c < N; c++) {
      display.frameBuffer[r][c] = image[r][c];
    }
  }
}

void displayRefresh(void) {
  /*
   * Display the image from the frame buffer
   * The image is displayed row by row
   */

  // Turn off the previous row
  digitalWrite(display.rowPins[display.currentRow], LOW);

  // Update the current row
  display.currentRow = (display.currentRow + 1) % N;

  // Turn ON/OFF the columns accordingly
  for (int c = 0; c < N; c++) {
    if (display.frameBuffer[display.currentRow][c] == 1)
      digitalWrite(display.colPins[c], LOW);
    else
      digitalWrite(display.colPins[c], HIGH);
  }

  // Turn ON the updated row
  digitalWrite(display.rowPins[display.currentRow], HIGH);
}

void SysTick_Handler(void) {
  displayRefresh(); // Called periodically
}
