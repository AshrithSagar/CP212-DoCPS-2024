#include "bot.h"

void bot_init(void) {
  int pinsM[] = {3, 2, 4, 31}; // M1A, M1B, M2A, M2B
  for (int i = 0; i < 4; i++) {
    pinMode(pinsM[i], OUTPUT);
  }
  motor_init(pinsM[0], pinsM[1], pinsM[2], pinsM[3]);

  encoder_init(28, 14, 37, 11); // M1E1, M1E2, M2E1, M2E2
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
