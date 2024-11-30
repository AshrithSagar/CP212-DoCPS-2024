#ifndef BUTTON_H
#define BUTTON_H

#include "gpio.h"

typedef struct {
  int pin;
  PinState state;
} Button;

void buttonInit(void);
bool isButtonPressed(const Button *button);

#endif // BUTTON_H
