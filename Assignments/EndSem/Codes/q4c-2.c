#include <stdint.h>

// From BSP
#define INPUT 0
#define OUTPUT 1
void pinMode(int pin, int mode);
void digitalWrite(int pin, int value);

#define LED_PIN 8
#define CLOCK 64000000UL // 64 MHz clock

// Macro to define IO registers
#define IOREG(base, offset) (*(volatile uint32_t *)((base) + (offset)))

// PWM Registers (replace addresses with actual values for nRF52833)
#define PWM0_BASE_ADDR 0x4001C000
#define PWM_ENABLE IOREG(PWM0_BASE_ADDR, 0x500)
#define PWM_MODE IOREG(PWM0_BASE_ADDR, 0x504)
#define PWM_COUNTERTOP IOREG(PWM0_BASE_ADDR, 0x508)
#define PWM_PRESCALER IOREG(PWM0_BASE_ADDR, 0x50C)
#define PWM_DECODER IOREG(PWM0_BASE_ADDR, 0x510)
#define PWM_SEQ0_PTR IOREG(PWM0_BASE_ADDR, 0x520)
#define PWM_SEQ0_CNT IOREG(PWM0_BASE_ADDR, 0x524)
#define PWM_SEQ0_REFRESH IOREG(PWM0_BASE_ADDR, 0x528)
#define PWM_SEQ0_ENDDELAY IOREG(PWM0_BASE_ADDR, 0x52C)
#define PWM_TASKS_SEQSTART0 IOREG(PWM0_BASE_ADDR, 0x008)

// PWM Duty Cycle Storage
volatile uint16_t
    pwmDutyCycle[1]; // Store one duty cycle value (0 to COUNTERTOP)

// Function to configure PWM
void pwmInit(uint32_t frequencyHz, uint8_t brightnessLevel) {
  // Calculate the COUNTERTOP value based on the desired frequency
  uint32_t countertop = CLOCK / frequencyHz;

  // Set the PWM frequency (COUNTERTOP register)
  PWM_COUNTERTOP = countertop - 1;

  // Set the prescaler (0 for the maximum base clock of 64 MHz)
  PWM_PRESCALER = 0;

  // Set the PWM mode to UP counter
  PWM_MODE = 0;

  // Configure decoder to load individual duty cycles
  PWM_DECODER = 0;

  // Configure the sequence pointer
  PWM_SEQ0_PTR = (uint32_t)pwmDutyCycle;
  PWM_SEQ0_CNT = 1; // One value in the sequence

  // Set initial brightness (convert brightnessLevel to duty cycle)
  pwmSetBrightness(brightnessLevel);

  // Enable PWM peripheral
  PWM_ENABLE = 1;

  // Start the sequence
  PWM_TASKS_SEQSTART0 = 1;
}

// Function to update brightness
void pwmSetBrightness(uint8_t brightnessLevel) {
  // Ensure brightnessLevel is within the valid range (0-10)
  if (brightnessLevel > 10) {
    brightnessLevel = 10;
  }

  // Convert brightness level to duty cycle (0 to COUNTERTOP range)
  uint32_t countertop = PWM_COUNTERTOP + 1;
  pwmDutyCycle[0] = (brightnessLevel * countertop) / 10;
}

// Main Function
int main() {
  // Set the LED pin as output
  pinMode(LED_PIN, OUTPUT);

  // Initialize PWM with a frequency of 1 kHz and brightness level of 5
  pwmInit(1000, 5);

  while (1) {
  }

  return 0;
}
