// From BSP
#define OUTPUT 1
void pinMode(int pin, int mode);

#define LED_PIN 8

// Function prototypes
void PWM_Init(int pin, int frequency);
void PWM_SetDutyCycle(int pin, int dutyCycle);

void setup() {
  // Set the LED pin as output
  pinMode(LED_PIN, OUTPUT);

  // Initialize PWM on LED_PIN with 1 kHz frequency
  PWM_Init(LED_PIN, 1000);
}

void setBrightnessLevel(int brightnessLevel) {
  if (brightnessLevel < 0)
    brightnessLevel = 0;
  if (brightnessLevel > 10)
    brightnessLevel = 10;

  // Calculate the duty cycle (0% to 100%)
  int dutyCycle = (brightnessLevel * 100) / 10;
  PWM_SetDutyCycle(LED_PIN, dutyCycle);
}

int main() {
  setup();
  while (1) {
    // Set some brightness level between 0-10
    setBrightnessLevel(5);

    // Additional logic can be implemented here without affecting PWM
  }
}
