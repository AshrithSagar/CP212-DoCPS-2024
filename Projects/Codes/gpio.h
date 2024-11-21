#ifndef GPIO_H
#define GPIO_H

#include <stdint.h>

#define LOW 0
#define HIGH 1
#define INPUT 0
#define OUTPUT 1
#define PULL_NONE 0
#define PULLDOWN (1 << 2)
#define PULLUP (3 << 2)
#define GPIO_RISINGEDGE 1
#define GPIO_FALLINGEDGE 2
#define GPIO_BOTHEDGES 3

void pinMode(int pin, int direction, int pull);
void digitalWrite(int pin, int value);
int digitalRead(int pin);
void digitalInterruptEnable(uint32_t pin, uint32_t edge, int event);

#endif // GPIO_H
