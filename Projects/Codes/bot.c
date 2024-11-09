#include "bot.h"

void bot_init(void) {
  int m1A = 2;
  int m1B = 3;
  int m2A = 12;
  int m2B = 37;
  pinMode(m1A, OUTPUT);
  pinMode(m1B, OUTPUT);
  pinMode(m2A, OUTPUT);
  pinMode(m2B, OUTPUT);
  motor_init(m1A, m1B, m2A, m2B);
  return;
}

void bot_forward(int speed) {
  motor_on(MOTOR_FORWARD, speed, MOTOR_FORWARD, speed);
  return;
}

void bot_reverse(int speed) {
  motor_on(MOTOR_REVERSE, speed, MOTOR_REVERSE, speed);
  return;
}

void bot_left(int speed) {
  motor_on(MOTOR_REVERSE, speed, MOTOR_FORWARD, speed);
  return;
}

void bot_right(int speed) {
  motor_on(MOTOR_FORWARD, speed, MOTOR_REVERSE, speed);
  return;
}

void bot_stop(void) {
  motor_off();
  return;
}
