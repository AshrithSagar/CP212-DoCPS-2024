#include <stdint.h>

// From BSP
#define INPUT 0
#define OUTPUT 1
void pinMode(int pin, int mode);
void digitalWrite(int pin, int value);

#define LOW 0
#define HIGH 1

#define LED_PIN 8

#define CLOCK 64000000UL // 64 MHz clock

#define IOREG(addr) (*((volatile long *)(addr)))

#define SYST_CSR IOREG(0xE000E010)
#define SYST_RVR IOREG(0xE000E014)
#define SYST_CVR IOREG(0xE000E018)

volatile int ledState = LOW;
// LED state (LOW or HIGH)
volatile int timeRemaining = 0;
// Time remaining for the current state (ON/OFF)

// Brightness level
volatile int brightnessLevel = 5;

// SysTick Interrupt Service Routine (ISR)
void SysTick_Handler(void) {
  if (timeRemaining > 0) {
    timeRemaining--;
  } else {
    // Toggle LED state
    ledState = !ledState;
    digitalWrite(LED_PIN, ledState);

    // Set timeRemaining based on the new state
    if (ledState == HIGH) {
      timeRemaining = (brightnessLevel * 100) / 10;
      // ON time
    } else {
      timeRemaining = 100 - (brightnessLevel * 100) / 10;
      // OFF time
    }
  }
}

void timerInterruptEnable(int ms) {
  /* Enable timer interrupts
   * Limitation of 250ms because of the timer overflow in hardware
   */

  SYST_RVR = ms * (CLOCK / 1000);
  /* SYST_RVR:
   * Technically, it should be
   * SYST_RVR = ms * (CLOCK / 1000) - 1;
   */

  SYST_CVR = 0;
  /* SYST_CVR:
   * Any write operation to CVR clears it
   */

  SYST_CSR = 7;
  /* SYST_CSR:
  - Bit-0: ENABLE; Enable/Disable clock;
    - (1) => Enable clock
  - Bit-1: TICKINT; Enabling interrupts;
    - (1) => Enable interrupts
  - Bit-2: CLKSOURCE; Internal/External clock;
    - (1) => Use internal clock (the only option in nRF52833)
  */
};

int main() {
  // Set the LED pin as output
  pinMode(LED_PIN, OUTPUT);

  // Initialize timer with 1ms resolution
  timerInterruptEnable(1);

  // Calculate initial ON time and
  // OFF time based on brightness level
  timeRemaining = (brightnessLevel * 100) / 10;
  // Initial ON time

  // The SysTick_Handler does all the work now
  while (1) {
  }

  return 0;
}
