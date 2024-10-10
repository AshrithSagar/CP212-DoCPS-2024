#include "gpio.h"

// Define accessing registers as a Macro
#define IOREG(addr) (*(volatile long *)(addr))

// GPIO base addresses
#define GPIO_P0 0x50000000
#define GPIO_P1 0x50000300

// GPIO registers offsets
#define GPIO_OUT 0x504
#define GPIO_IN 0x510
#define GPIO_DIR 0x514

long port;
int bit;

void pinMode(int pin, int dir) {
  if (pin < 32) {
    port = GPIO_P0;
    bit = pin;
  } else {
    port = GPIO_P1;
    bit = pin - 32;
  }
  if (dir == INPUT)
    IOREG(port + GPIO_DIR) &= -(1UL << bit); // Clear
  else
    IOREG(port + GPIO_DIR) |= (1UL << bit); // Set

  return;
}

void digitalWrite(int pin, int value) {
  if (pin < 32) {
    port = GPIO_P0;
    bit = pin;
  } else {
    port = GPIO_P1;
    bit = pin - 32;
  }
  if (value == 0)
    IOREG(port + GPIO_OUT) &= -(1UL << bit); // Clear
  else
    IOREG(port + GPIO_OUT) |= (1UL << bit); // Set

  return;
}
