#include "bot.h"

void bot_init(void) {
  int pins[] = {2, 3, 12, 37}; // M1A, M1B, M2A, M2B
  for (int i = 0; i < 4; i++) {
    pinMode(pins[i], OUTPUT);
  }
  motor_init(pins[0], pins[1], pins[2], pins[3]);
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
