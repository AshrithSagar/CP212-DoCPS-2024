/* Hardware abstraction layer for GPIO port */
#include "gpio.h"
#include "encoder.h"
#include "nrf52833.h"

// Macros
#define IOREG32(addr) (*((volatile uint32_t *)(uintptr_t)(addr)))
#define GPIO_PORT(pin) ((pin) < 32 ? NRF_P0 : NRF_P1)
#define GPIO_BIT(pin) ((pin) < 32 ? (pin) : ((pin)-32))
#define GPIOTE_MODEEVENT (1)
#define NVIC_ISER IOREG32(0xE000E100)

void pinMode(int pin, PinMode direction, PullType pull) {
  /*
   * Set the direction of a GPIO pin
   * pin: pin number
   * direction: INPUT or OUTPUT
   * pull: PULL_NONE, PULLDOWN, or PULLUP
   */

  NRF_GPIO_Type *port = GPIO_PORT(pin);
  uint32_t bit = GPIO_BIT(pin);

  if (direction == INPUT) {
    port->DIRCLR &= ~(1UL << bit);
    port->PIN_CNF[bit] = pull;
  } else if (direction == OUTPUT) {
    port->DIRSET |= (1UL << bit);
    port->PIN_CNF[bit] = OUTPUT;
  }
}

void digitalWrite(int pin, PinState value) {
  /*
   * Write a value to a GPIO pin
   * pin: pin number
   * value: LOW or HIGH
   */

  NRF_GPIO_Type *port = GPIO_PORT(pin);
  uint32_t bit = GPIO_BIT(pin);

  if (value == LOW)
    port->OUTCLR &= ~(1UL << bit);
  else if (value == HIGH)
    port->OUTSET |= (1UL << bit);
}

int digitalRead(int pin) {
  NRF_GPIO_Type *port = GPIO_PORT(pin);
  uint32_t bit = GPIO_BIT(pin);

  return (port->IN >> bit) & 0x01;
}

void digitalInterruptEnable(uint32_t pin, InterruptEdge edge, int event) {
  /* GPIOTE has 8 registers, each can be configured for event i (i = 0 to 7)
   * along with the pin number and event type associated with the event.
   */
  NRF_GPIOTE->CONFIG[event] = (GPIOTE_MODEEVENT | (pin << 8) | (edge << 16));

  // Generate an interrupt when the specified event occurs.
  NRF_GPIOTE->INTENSET |= (1 << event);

  // Enable GPIOTE interrupts in the interrupt controller
  NVIC_ISER |= (1 << GPIOTE_IRQn);
}

void GPIOTE_IRQHandler(void) {
  /* Handle GPIO tasks and events */

  if (NRF_GPIOTE->EVENTS_IN[0]) {
    encoder_update(0);
    NRF_GPIOTE->EVENTS_IN[0] = 0;
  }

  if (NRF_GPIOTE->EVENTS_IN[1]) {
    encoder_update(1);
    NRF_GPIOTE->EVENTS_IN[1] = 0;
  }
}
