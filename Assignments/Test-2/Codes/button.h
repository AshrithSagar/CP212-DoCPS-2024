#ifndef GPIO_H
#define GPIO_H
#include "gpio.h"
#endif // GPIO_H

#define BTN_A 14
#define BTN_B 23

#define BUTTON_PRESSED(button) (digitalRead(button) == LOW)

void buttonInit(void);
