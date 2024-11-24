/* Push buttons driver */
#include "button.h"
#include "gpio.h"
#include <stdbool.h>

Button btnA = {14, HIGH};
Button btnB = {23, HIGH};

void buttonInit(void) {
  /* Initialize the button pins as INPUT */
  pinMode(btnA.pin, INPUT, PULL_NONE);
  pinMode(btnB.pin, INPUT, PULL_NONE);
}

bool isButtonPressed(const Button *button) {
  /* Read the button state and return true if pressed */
  return digitalRead(button->pin) == LOW;
}
