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
} Encoder;

typedef struct {
  Encoder encoder;
} Motor;

Motor motor1;
Motor motor2;

void Motor_init(Motor *motor1, Motor *motor2, int M1E1, int M1E2, int M2E1,
                int M2E2) {
  motor1->encoder.pinE1 = M1E1;
  motor1->encoder.pinE2 = M1E2;
  motor1->encoder.counter = 0;
  motor1->encoder.timer.current = 0;
  motor1->encoder.timer.previous = 0;
  motor1->encoder.timer.diff = 0;

  motor2->encoder.pinE1 = M2E1;
  motor2->encoder.pinE2 = M2E2;
  motor2->encoder.counter = 0;
  motor2->encoder.timer.current = 0;
  motor2->encoder.timer.previous = 0;
  motor2->encoder.timer.diff = 0;

  pinMode(M1E1, INPUT, PULLDOWN);
  digitalInterruptEnable(M1E1, GPIO_RISINGEDGE, 0);

  pinMode(M2E1, INPUT, PULLDOWN);
  digitalInterruptEnable(M2E1, GPIO_RISINGEDGE, 1);
}

float Motor_getSpeed(Motor *motor, int pin) {
  if (pin == motor->encoder.pinE1 && motor->encoder.timer.diff != 0)
    return ((float)NUM_MS_IN_MIN / motor->encoder.timer.diff) / PPR;
  else if (pin == motor->encoder.pinE2 && motor->encoder.timer.diff != 0)
    return ((float)NUM_MS_IN_MIN / motor->encoder.timer.diff) / PPR;
  else
    return 0;
}

float Motor_getRPM(Motor *motor) {
  /* Calculate the RPM of the motor
   * RPM = (Counter * 60) / PPR
   */
  return (float)(motor->encoder.counter * 60) / PPR;
}

void encoder_updateTimer(Motor *motor) {
  motor->encoder.timer.current = timer32_read();
  motor->encoder.timer.diff =
      motor->encoder.timer.current - motor->encoder.timer.previous;
  motor->encoder.timer.previous = motor->encoder.timer.current;
}

void encoder_updateCounter(Motor *motor) {
  motor->encoder.counter++;
  myprintf("Counter: %d\n", motor->encoder.counter);
}

void encoder_init(int M1E1, int M1E2, int M2E1, int M2E2) {
  Motor_init(&motor1, &motor2, M1E1, M1E2, M2E1, M2E2);
  timer32_init();
}

void encoder_update(int event) {
  if (event == 0) {
    encoder_updateTimer(&motor1);
    encoder_updateCounter(&motor1);
  } else if (event == 1) {
    encoder_updateTimer(&motor2);
    encoder_updateCounter(&motor2);
  }
}
