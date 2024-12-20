#ifndef GPIO_H
#define GPIO_H

#include <stdint.h>

typedef enum { INPUT = 0, OUTPUT = 1 } PinMode;
typedef enum { LOW = 0, HIGH = 1 } PinState;
typedef enum {
  PULL_NONE = 0,
  PULL_DOWN = (1 << 2),
  PULL_UP = (3 << 2)
} PullType;
typedef enum {
  GPIO_RISINGEDGE = 1,
  GPIO_FALLINGEDGE = 2,
  GPIO_BOTHEDGES = 3
} InterruptEdge;

void pinMode(int pin, PinMode direction, PullType pull);
void digitalWrite(int pin, PinState value);
PinState digitalRead(int pin);
void digitalInterruptEnable(uint32_t pin, InterruptEdge edge, int event);

#endif // GPIO_H
