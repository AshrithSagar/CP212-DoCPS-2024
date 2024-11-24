/* Push buttons driver */
#include "button.h"
#include "gpio.h"

typedef struct {
  int pin;
  PinState state;
} Button;

#define BTN_A_PIN 14
#define BTN_B_PIN 23

Button btnA = {BTN_A_PIN, HIGH};
Button btnB = {BTN_B_PIN, HIGH};

#define BUTTON_PRESSED(button) (digitalRead(button.pin) == LOW)

void buttonInit(void) {
  /* Initialize the button pins as INPUT */
  pinMode(btnA.pin, INPUT, PULL_NONE);
  pinMode(btnB.pin, INPUT, PULL_NONE);
}

void updateButtonState(Button *button) {
  button->state = digitalRead(button->pin);
}
