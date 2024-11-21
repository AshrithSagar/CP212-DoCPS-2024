/* Hardware abstraction layer for GPIO port */
#include "gpio.h"
#include "printlib.h"

// Macros
#define IOREG(addr) (*((volatile long *)(addr)))
#define IOREG32(addr) (*((volatile uint32_t *)(uintptr_t)(addr)))
#define GPIO_PORT(pin) ((pin) < 32 ? GPIO_P0 : GPIO_P1)
#define GPIO_BIT(pin) ((pin) < 32 ? (pin) : (pin) - 32)
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

// GPIOTE registers
#define GPIOTE_EVENTSIN(i) IOREG32(0x40006100 + 4 * (i))
#define GPIOTE_INTENSET IOREG32(0x40006304)
#define GPIOTE_CONFIG(i) IOREG32(0x40006510 + 4 * (i))
#define GPIOTE_MODEEVENT (1)

// NVIC registers
#define NVIC_ISER IOREG32(0xE000E100)
#define GPIOTE_ID 6 // Peripheral ID

void pinMode(int pin, PinMode direction, PullType pull) {
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

void digitalWrite(int pin, PinState value) {
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

void digitalInterruptEnable(uint32_t pin, InterruptEdge edge, int event) {
  /* GPIOTE has 8 registers, each can be configured for event i (i = 0 to 7)
   * along with the pin number and event type associated with the event.
   */
  GPIOTE_CONFIG(event) = (GPIOTE_MODEEVENT | (pin << 8) | (edge << 16));
  myprintf("GPIOTE_CONFIG(%d) = %x\n", event, GPIOTE_CONFIG(event));

  // Generate an interrupt when the specified event occurs.
  GPIOTE_INTENSET |= (1 << event);

  // Enable GPIOTE interrupts in the interrupt controller
  NVIC_ISER |= (1 << GPIOTE_ID);
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

  if (GPIOTE_EVENTSIN(0)) {
    encoder_update_test(0);
    GPIOTE_EVENTSIN(0) = 0;
  }

  if (GPIOTE_EVENTSIN(1)) {
    encoder_update_test(1);
    GPIOTE_EVENTSIN(1) = 0;
  }
}
