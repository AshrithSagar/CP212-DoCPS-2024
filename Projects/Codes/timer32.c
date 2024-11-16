#include "timer32.h"

void timer32_init() {
  // Set Timer0 to 32-bit mode
  NRF_TIMER0->BITMODE = 3;

  // Set prescaler to 4 to achieve 1 MHz timer frequency (16 MHz / 2^4 = 1 MHz)
  NRF_TIMER0->PRESCALER = 4;

  // Set Timer mode to Timer (not Counter)
  NRF_TIMER0->MODE = 0;

  // Clear the timer
  NRF_TIMER0->TASKS_CLEAR = 1;

  // Start the timer
  NRF_TIMER0->TASKS_START = 1;
}

unsigned long timer32_read() {
  // Capture current timer value to CC[0] register
  NRF_TIMER0->TASKS_CAPTURE[0] = 1;

  // Return the captured value
  return NRF_TIMER0->CC[0];
}
