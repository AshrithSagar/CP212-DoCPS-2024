#include "encoder.h"
#include "bot.h"
#include "gpio.h"
#include "printlib.h"
#include "timer32.h"

#define NUM_MICROS_IN_MIN (60000000L) // Microseconds in a minute
#define PPR 325                       // Pulses per revolution

void configureEncoder(Motor *motor, int pinE1, int pinE2) {
  motor->encoder.pinE1 = pinE1;
  motor->encoder.pinE2 = pinE2;
  motor->encoder.counter = 0;
  motor->encoder.timer.current = 0;
  motor->encoder.timer.previous = 0;
  motor->encoder.timer.diff = 0;

  pinMode(pinE1, INPUT, PULL_DOWN);
  digitalInterruptEnable(pinE1, GPIO_RISINGEDGE, motor->id);
}

void encoder_updateTimer(Motor *motor) {
  motor->encoder.timer.current = timer32_read();
  motor->encoder.timer.diff =
      motor->encoder.timer.current - motor->encoder.timer.previous;
  motor->encoder.timer.previous = motor->encoder.timer.current;
}

void encoder_updateCounter(Motor *motor) { motor->encoder.counter++; }

float motor_getSpeed(Motor *motor) {
  /* Calculate the speed of the motor
   * rev/min = (microseconds per minute) / (
   *  (microseconds per pulse) * (pulses per revolution))
   */

  if (motor->encoder.timer.diff != 0)
    return ((float)NUM_MICROS_IN_MIN / motor->encoder.timer.diff) / PPR;
  return 0.0;
}

float motor_getRPM(Motor *motor) {
  /* Calculate the RPM of the motor
   * RPM = (Counter * 60) / PPR
   */
  return (float)(motor->encoder.counter * 60) / PPR;
}

Motor motorLeft, motorRight;
void encoder_init(StackBot *bot) {
  motorLeft = bot->motorLeft;
  motorRight = bot->motorRight;
  configureEncoder(&motorLeft, bot->encoderPins.M1E1, bot->encoderPins.M1E2);
  configureEncoder(&motorRight, bot->encoderPins.M2E1, bot->encoderPins.M2E2);
  timer32_init();
}

void encoder_update(int event) {
  Motor *motor = (event == 0) ? &motorLeft : &motorRight;
  encoder_updateTimer(motor);
  encoder_updateCounter(motor);

  myprintf("Motor 1: %f\tMotor 2: %f\n", motor_getSpeed(&motorLeft),
           motor_getSpeed(&motorRight));
}
