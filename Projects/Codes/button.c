/* Push buttons driver */
#include "button.h"
#include "gpio.h"

#define BTN_A 14
#define BTN_B 23

#define BUTTON_PRESSED(button) (digitalRead(button) == LOW)

void buttonInit(void) {
  /* Initialize the button pins as INPUT */

  pinMode(BTN_A, INPUT, PULL_NONE);
  pinMode(BTN_B, INPUT, PULL_NONE);

  return;
}
