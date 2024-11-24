#ifndef BUTTON_H
#define BUTTON_H

#include "gpio.h"

typedef struct {
  int pin;
  PinState state;
} Button;

void buttonInit(void);

#endif // BUTTON_H
