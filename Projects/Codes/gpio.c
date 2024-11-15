/* Hardware abstraction layer for GPIO port */
#include "gpio.h"

// GPIO base addresses
#define GPIO_P0 0x50000000
#define GPIO_P1 0x50000300

// GPIO registers offsets
#define GPIO_OUT 0x504
#define GPIO_IN 0x510
#define GPIO_DIR 0x514

#define GPIO_CONFIG(pin) (0x700 + (pin) * 4)

// Macros
#define IOREG(addr) (*((volatile long *)(addr)))
#define GPIO_PORT(pin) ((pin) < 32 ? GPIO_P0 : GPIO_P1)
#define GPIO_BIT(pin) ((pin) < 32 ? (pin) : (pin) - 32)
#define CLEAR(port, offset, bit) (IOREG(port + offset) &= ~(1UL << (bit)))
#define SET(port, offset, bit) (IOREG(port + offset) |= (1UL << (bit)))

void pinMode(int pin, int dir) {
  /*
   * Set the direction of a GPIO pin
   * pin: pin number
   * dir: INPUT or OUTPUT
   */

  long port;
  int bit;
  port = GPIO_PORT(pin);
  bit = GPIO_BIT(pin);

  if (dir == INPUT) {
    CLEAR(port, GPIO_DIR, bit);
    IOREG(port + GPIO_CONFIG(bit)) = INPUT;
  } else if (dir == OUTPUT) {
    SET(port, GPIO_DIR, bit);
    IOREG(port + GPIO_CONFIG(bit)) = OUTPUT;
  }

  return;
}

void digitalWrite(int pin, int value) {
  /*
   * Write a value to a GPIO pin
   * pin: pin number
   * value: LOW or HIGH
   */

  long port;
  int bit;
  port = GPIO_PORT(pin);
  bit = GPIO_BIT(pin);

  if (value == LOW)
    CLEAR(port, GPIO_OUT, bit);
  else if (value == HIGH)
    SET(port, GPIO_OUT, bit);

  return;
}

int digitalRead(int pin) {
  long port;
  int bit, read;
  port = GPIO_PORT(pin);
  bit = GPIO_BIT(pin);

  read = ((IOREG(port + GPIO_IN) >> bit) & 0x01);
  return read;
}
