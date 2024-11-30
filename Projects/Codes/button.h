#ifndef BUTTON_H
#define BUTTON_H

#include "bot.h"
#include "gpio.h"
#include <stdbool.h>

typedef struct {
  int pin;
  PinState state;
} Button;

void button_init(StackBot *bot);
bool isButtonPressed(const Button *button);

#endif // BUTTON_H
