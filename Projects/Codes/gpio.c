/* Hardware abstraction layer for GPIO port */
#include "gpio.h"
#include "nrf52833.h"
#include "printlib.h"

// Macros
#define IOREG(addr) (*((volatile long *)(addr)))
#define IOREG32(addr) (*((volatile uint32_t *)(uintptr_t)(addr)))
#define GPIO_PORT(pin) ((pin) < 32 ? GPIO_P0 : GPIO_P1)
#define GPIO_BIT(pin) ((pin) < 32 ? (pin) : ((pin) - 32))
#define CLEAR(port, offset, bit) (IOREG(port + offset) &= ~(1UL << (bit)))
#define SET(port, offset, bit) (IOREG(port + offset) |= (1UL << (bit)))

// GPIO base addresses
#define GPIO_P0 0x50000000UL
#define GPIO_P1 0x50000300UL

// GPIO registers offsets
#define GPIO_OUT 0x504
#define GPIO_IN 0x510
#define GPIO_DIR 0x514

// GPIO configuration registers
#define GPIO_CONFIG(pin) (0x700 + (pin) * 4)

void pinMode(int pin, int direction, int pull) {
  /*
   * Set the direction of a GPIO pin
   * pin: pin number
   * direction: INPUT or OUTPUT
   * pull: PULL_NONE, PULLDOWN, or PULLUP
   */

  unsigned long port, bit;
  port = GPIO_PORT(pin);
  bit = GPIO_BIT(pin);

  if (direction == INPUT) {
    CLEAR(port, GPIO_DIR, bit);
    IOREG(port + GPIO_CONFIG(bit)) = pull;
  } else if (direction == OUTPUT) {
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

// GPIOTE & NVIC
#define GPIOTE_MODEEVENT (1)
#define NVIC_ISER IOREG32(0xE000E100)

void digitalInterruptEnable(uint32_t pin, uint32_t edge, int event) {
  /* GPIOTE has 8 registers, each can be configured for event i (i = 0 to 7)
   * along with the pin number and event type associated with the event.
   */
  NRF_GPIOTE->CONFIG[event] = (GPIOTE_MODEEVENT | (pin << 8) | (edge << 16));

  // Generate an interrupt when the specified event occurs.
  NRF_GPIOTE->INTENSET |= (1 << event);

  // Enable GPIOTE interrupts in the interrupt controller
  NVIC_ISER |= (1 << GPIOTE_IRQn);
}

int counter1 = 0;
int counter2 = 0;
void encoder_update_test(int event) {
  if (event == 0) {
    counter1++;
    myprintf("Motor 1: %d\n", counter1);
  } else if (event == 1) {
    counter2++;
    myprintf("Motor 2: %d\n", counter2);
  }
}

void GPIOTE_IRQHandler(void) {
  /* Handle GPIO tasks and events */

  if (NRF_GPIOTE->EVENTS_IN[0]) {
    encoder_update_test(0);
    NRF_GPIOTE->EVENTS_IN[0] = 0;
  }

  if (NRF_GPIOTE->EVENTS_IN[1]) {
    encoder_update_test(1);
    NRF_GPIOTE->EVENTS_IN[1] = 0;
  }
}
