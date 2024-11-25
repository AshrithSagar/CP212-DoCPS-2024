// From BSP
#define INPUT 0
#define OUTPUT 1
void pinMode(int pin, int mode);
void digitalWrite(int pin, int value);

#include "nrf52833.h"
#include <stdint.h>

#define LOW 0
#define HIGH 1

#define LED_PIN 8

// Global variables
volatile int brightnessLevel = 5; // Brightness level (0-10)
volatile int onTime = 0;          // ON duration in ms
volatile int offTime = 0;         // OFF duration in ms
volatile int ledState = LOW;      // Current state of the LED
volatile int counter = 0;         // Counter for timing
extern uint32_t SystemCoreClock;  // Declare SystemCoreClock

// Function prototypes
void timer32_init(void);
void TIMER0_IRQHandler(void);

void setup() {
  // Set the LED pin as output
  pinMode(LED_PIN, OUTPUT);

  // Initialize Timer32 peripheral
  timer32_init();
}

void timer32_init() {
  // Set Timer0 to 32-bit mode
  NRF_TIMER0->BITMODE = 3;

  // Set prescaler to 4 to achieve 1 MHz timer frequency
  // (16 MHz / 2^4 = 1 MHz)
  NRF_TIMER0->PRESCALER = 4;

  // Set Mode to Timer
  NRF_TIMER0->MODE = 0;

  // Clear the timer
  NRF_TIMER0->TASKS_CLEAR = 1;

  // Enable interrupt for Timer0
  NRF_TIMER0->INTENSET = (1 << 16);
  // Compare event 0

  // Set compare register to 1 ms
  // (1 MHz timer frequency)
  NRF_TIMER0->CC[0] = 1000;

  // Enable Timer0 interrupt in NVIC
  NVIC_EnableIRQ(TIMER0_IRQn);

  // Start the timer
  NRF_TIMER0->TASKS_START = 1;
}

// Timer0 interrupt handler
void TIMER0_IRQHandler(void) {
  if (NRF_TIMER0->EVENTS_COMPARE[0]) {
    NRF_TIMER0->EVENTS_COMPARE[0] = 0;
    // Clear the compare event

    counter++;

    // Determine ON/OFF duration based on brightness level
    onTime = (brightnessLevel * 100) / 10;
    offTime = 100 - onTime;

    // Toggle LED state based on timing
    if (ledState == HIGH) {
      // If the ON time has elapsed
      if (counter >= onTime) {
        digitalWrite(LED_PIN, LOW); // Turn LED OFF
        ledState = LOW;             // Update the LED state
        counter = 0;                // Reset the counter
      }
    } else {
      // If the OFF time has elapsed
      if (counter >= offTime) {
        digitalWrite(LED_PIN, HIGH); // Turn LED ON
        ledState = HIGH;             // Update the LED state
        counter = 0;                 // Reset the counter
      }
    }

    // Reset the timer for the next interrupt
    NRF_TIMER0->TASKS_CLEAR = 1;
    NRF_TIMER0->TASKS_START = 1;
  }
}

int main() {
  setup();
  while (1) {
    /* Main loop can perform other tasks
     * while Timer32 manages LED brightness
     */
  }
}
