#include "encoder.h"

typedef struct {
  int pinE1, pinE2;
  int counter;
  int lastStateE1;
  int lastStateE2;
} Motor;

void Motor_init(Motor *motor, int pinE1, int pinE2) {
  motor->pinE1 = pinE1;
  motor->pinE2 = pinE2;
  motor->counter = 0;
  motor->lastStateE1 = HIGH;
  motor->lastStateE2 = HIGH;

  pinMode(pinE1, INPUT, INPUT);
  pinMode(pinE2, INPUT, INPUT);
}

void Motor_updateEncoder(Motor *motor) {
  int currentE1 = digitalRead(motor->pinE1);

  if (motor->lastStateE1 == LOW && currentE1 == HIGH) {
    motor->counter++; // Rising edge detected
    myprintf("Counter E1: %d\n", motor->counter);
  } else if (motor->lastStateE1 == HIGH && currentE1 == LOW) {
    motor->counter++; // Falling edge detected
    myprintf("Counter E1: %d\n", motor->counter);
  }

  motor->lastStateE1 = currentE1;
}

Motor motor1;
Motor motor2;

void encoder_init(int M1E1, int M1E2, int M2E1, int M2E2) {
  Motor_init(&motor1, M1E1, M1E2);
  Motor_init(&motor2, M2E1, M2E2);
  uart_init();
}

void encoder_counter() {
  Motor_updateEncoder(&motor1);
  Motor_updateEncoder(&motor2);
}
