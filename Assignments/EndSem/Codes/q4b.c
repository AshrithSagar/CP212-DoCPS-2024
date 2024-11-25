// From BSP
#define INPUT 0
#define OUTPUT 1
void pinMode(int pin, int mode);
void digitalWrite(int pin, int value);

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
void SysTickInit(void);
void SysTick_Handler(void);

void setup() {
  // Set the LED pin as output
  pinMode(LED_PIN, OUTPUT);

  // Initialize SysTick timer for interrupts
  SysTickInit();
}

void SysTickInit() {}

// SysTick interrupt handler
void SysTick_Handler(void) {
  counter++;

  // Determine ON/OFF duration based on brightness level
  onTime = (brightnessLevel * 100) / 10;
  offTime = 100 - onTime;

  // Toggle LED state based on timing
  if (ledState == HIGH) {
    if (counter >= onTime) {      // If the ON time has elapsed
      digitalWrite(LED_PIN, LOW); // Turn LED OFF
      ledState = LOW;             // Update the LED state
      counter = 0;                // Reset the counter
    }
  } else {
    if (counter >= offTime) {      // If the OFF time has elapsed
      digitalWrite(LED_PIN, HIGH); // Turn LED ON
      ledState = HIGH;             // Update the LED state
      counter = 0;                 // Reset the counter
    }
  }
}

int main() {
  setup();
  while (1) {
    /* Main loop can perform other tasks
     * while SysTick manages LED brightness
     */
  }
}
