// From BSP
#define INPUT 0
#define OUTPUT 1
void pinMode(int pin, int mode);
void digitalWrite(int pin, int value);

#define LOW 0
#define HIGH 1

#define LED_PIN 8

void SysTickDelay(int milliseconds);

void setup() {
  // Set the LED pin as output
  pinMode(LED_PIN, OUTPUT);
}

// Function to control LED brightness
void loop() {
  // Set the brightness level to a value between 0 and 10
  int brightnessLevel = 5;

  // Calculate the ON time and OFF time based on brightness level
  // Using percentage values
  int onTime = (brightnessLevel * 100) / 10;
  int offTime = 100 - onTime;

  // If brightness level is 0, keep LED off
  if (brightnessLevel == 0) {
    digitalWrite(LED_PIN, LOW);
    return;
  }

  // Turn the LED ON
  digitalWrite(LED_PIN, HIGH);
  SysTickDelay(onTime); // Wait for ON time

  // Turn the LED OFF
  digitalWrite(LED_PIN, LOW);
  SysTickDelay(offTime); // Wait for OFF time
}

int main() {
  setup();
  while (1) {
    loop();
  }
}
