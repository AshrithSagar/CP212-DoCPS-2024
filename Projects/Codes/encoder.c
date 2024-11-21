#include "encoder.h"
#include "gpio.h"
#include "printlib.h"
#include "timer32.h"
#include <stdint.h>

#define NUM_MS_IN_MIN (60000000L) // Microseconds in a minute
#define PPR 325                   // Pulses per revolution

typedef struct {
  unsigned long current;
  unsigned long previous;
  unsigned long diff;
} Timer;

typedef struct {
  int pinE1, pinE2;
  int counter;
  int lastStateE1;
  int lastStateE2;
  Timer timer;
} Motor;

void Motor_init(Motor *motor1, Motor *motor2, int M1E1, int M1E2, int M2E1,
                int M2E2) {
  motor1->pinE1 = M1E1;
  motor1->pinE2 = M1E2;
  motor1->counter = 0;
  motor1->timer.current = 0;
  motor1->timer.previous = 0;
  motor1->timer.diff = 0;

  motor2->pinE1 = M2E1;
  motor2->pinE2 = M2E2;
  motor2->counter = 0;
  motor2->timer.current = 0;
  motor2->timer.previous = 0;
  motor2->timer.diff = 0;

  pinMode(M1E1, INPUT, PULLDOWN);
  digitalInterruptEnable(M1E1, GPIO_RISINGEDGE, 0);

  pinMode(M2E1, INPUT, PULLDOWN);
  digitalInterruptEnable(M2E1, GPIO_RISINGEDGE, 1);
}

float Motor_getSpeed(Motor *motor, int pin) {
  if (pin == motor->pinE1 && motor->timer.diff != 0)
    return ((float)NUM_MS_IN_MIN / motor->timer.diff) / PPR;
  else if (pin == motor->pinE2 && motor->timer.diff != 0)
    return ((float)NUM_MS_IN_MIN / motor->timer.diff) / PPR;
  else
    return 0;
}

float Motor_getRPM(Motor *motor) {
  /* Calculate the RPM of the motor
   * RPM = (Counter * 60) / PPR
   */
  return (float)(motor->counter * 60) / PPR;
}

void Motor_updateCounter(Motor *motor1, Motor *motor2, int event) {
  if (event == 0) {
    motor1->counter++;
    myprintf("Motor 1: %d\n", motor1->counter);
  } else if (event == 1) {
    motor2->counter++;
    myprintf("Motor 2: %d\n", motor2->counter);
  }
}

void Motor_updateEncoder(Motor *motor, int event) {
  if (event == 0) {
    motor->timer.current = timer32_read();
    motor->timer.diff = motor->timer.current - motor->timer.previous;
    motor->timer.previous = motor->timer.current;
  } else if (event == 1) {
    motor->timer.current = timer32_read();
    motor->timer.diff = motor->timer.current - motor->timer.previous;
    motor->timer.previous = motor->timer.current;
  }
}

Motor motor1;
Motor motor2;

void encoder_init(int M1E1, int M1E2, int M2E1, int M2E2) {
  Motor_init(&motor1, &motor2, M1E1, M1E2, M2E1, M2E2);
  timer32_init();
}

void encoder_update(int event) {
  Motor_updateEncoder(&motor1, event);
  Motor_updateEncoder(&motor2, event);
  Motor_updateCounter(&motor1, &motor2, event);
}
