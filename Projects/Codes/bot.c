#include "bot.h"
#include "encoder.h"
#include "gpio.h"
#include "motor.h"

void bot_init(StackBot *bot) {
  for (int i = 0; i < 4; i++) {
    pinMode(bot->motorPins[i], OUTPUT, PULL_NONE);
  }
  motor_init(bot->motorPins[0], bot->motorPins[1], bot->motorPins[2],
             bot->motorPins[3]);
  encoder_init(bot->encoderPins[0], bot->encoderPins[1], bot->encoderPins[2],
               bot->encoderPins[3]);
}

void bot_forward(StackBot *bot, int speed) {
  motor_on(MOTOR_REVERSE, speed, MOTOR_FORWARD, speed);
}

void bot_reverse(StackBot *bot, int speed) {
  motor_on(MOTOR_FORWARD, speed, MOTOR_REVERSE, speed);
}

void bot_left(StackBot *bot, int speed) {
  motor_on(MOTOR_FORWARD, speed, MOTOR_FORWARD, speed);
}

void bot_right(StackBot *bot, int speed) {
  motor_on(MOTOR_REVERSE, speed, MOTOR_REVERSE, speed);
}

void bot_stop(StackBot *bot) { motor_off(); }

void bot_create(StackBot *bot) {
  bot->motorPins[0] = 3;    // M1A
  bot->motorPins[1] = 2;    // M1B
  bot->motorPins[2] = 4;    // M2A
  bot->motorPins[3] = 31;   // M2B
  bot->encoderPins[0] = 28; // M1E1
  bot->encoderPins[1] = 14; // M1E2
  bot->encoderPins[2] = 37; // M2E1
  bot->encoderPins[3] = 11; // M2E2
  bot->init = bot_init;
  bot->forward = bot_forward;
  bot->reverse = bot_reverse;
  bot->left = bot_left;
  bot->right = bot_right;
  bot->stop = bot_stop;
}
