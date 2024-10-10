#include "display.h"
#include "gpio.h"

int LED_ROWS[] = {21, 22, 15, 24, 19};
int LED_COLS[] = {28, 11, 31, 37, 30};

int delay(int ms) {
  int clocks = ms * 64000;
  // 64000 clock cycles in 1ms.

  while (clocks >= 0) {
    clocks -= 10;
  }

  return 0;
}

void displayInit(void) {
  for (int i = 0; i < N; i++) {
    digitalWrite(LED_ROWS[i], 0);
    pinMode(LED_ROWS[i], OUTPUT);

    digitalWrite(LED_COLS[i], 1);
    pinMode(LED_COLS[i], OUTPUT);
  }
  return;
}

void display(char image[N][N]) {
  for (int r = 0; r < N; r++) {
    // Turn ON the row
    digitalWrite(LED_ROWS[r], 1);
    for (int c = 0; c < N; c++) {
      if (image[r][c] == 1)
        // Selectively turn ON the columns
        digitalWrite(LED_COLS[c], 0);
    }

    delay(5); // 8 ms * 5 rows => 40 ms * 25 frames = 1 second

    // Turn OFF all the columns
    for (int c = 0; c < N; c++) {
      digitalWrite(LED_COLS[c], 1);
    }

    // Turn OFF the row
    digitalWrite(LED_ROWS[r], 0);
  }

  return;
}
