#include "encoder.h"
#include "gpio.h"
#include "printlib.h"
#include "timer32.h"
#include <stdint.h>

#define NUM_MS_IN_MIN (60000000L) // Microseconds in a minute
#define PPR 325                   // Pulses per revolution

unsigned long timer_m1, timer_m1_prev, timer_m1_diff;
unsigned long timer_m2, timer_m2_prev, timer_m2_diff;

typedef struct {
  int pinE1, pinE2;
  int counter;
  int lastStateE1;
  int lastStateE2;
} Motor;

void Motor_init(Motor *motor1, Motor *motor2, int M1E1, int M1E2, int M2E1,
                int M2E2) {
  motor1->pinE1 = M1E1;
  motor1->pinE2 = M1E2;
  motor1->counter = 0;

  motor2->pinE1 = M2E1;
  motor2->pinE2 = M2E2;
  motor2->counter = 0;

  pinMode(M1E1, INPUT, PULLDOWN);
  digitalInterruptEnable(M1E1, GPIO_RISINGEDGE, 0);

  pinMode(M2E1, INPUT, PULLDOWN);
  digitalInterruptEnable(M2E1, GPIO_RISINGEDGE, 1);

  timer_m1 = 0;
  timer_m1_prev = 0;
  timer_m1_diff = 0;
  timer_m2 = 0;
  timer_m2_prev = 0;
  timer_m2_diff = 0;
}

float Motor_getSpeed(Motor *motor, int pin) {
  if (pin == motor->pinE1 && timer_m1_diff != 0)
    return ((float)NUM_MS_IN_MIN / timer_m1_diff) / PPR;
  else if (pin == motor->pinE2 && timer_m2_diff != 0)
    return ((float)NUM_MS_IN_MIN / timer_m2_diff) / PPR;
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
    timer_m1 = timer32_read();
    timer_m1_diff = timer_m1 - timer_m1_prev;
    timer_m1_prev = timer_m1;
  } else if (event == 1) {
    timer_m2 = timer32_read();
    timer_m2_diff = timer_m2 - timer_m2_prev;
    timer_m2_prev = timer_m2;
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
