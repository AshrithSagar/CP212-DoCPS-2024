/* Push buttons driver */
#include "button.h"
#include "bot.h"
#include "gpio.h"
#include <stdbool.h>

void button_init(StackBot *bot) {
  /* Initialize the button pins as INPUT */
  pinMode(bot->buttonPins.btnA, INPUT, PULL_NONE);
  pinMode(bot->buttonPins.btnB, INPUT, PULL_NONE);
}

bool isButtonPressed(const Button *button) {
  /* Read the button state and return true if pressed */
  return digitalRead(button->pin) == LOW;
}
