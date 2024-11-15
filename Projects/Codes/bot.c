#include "bot.h"

void bot_init(Bot *bot) {
  for (int i = 0; i < 4; i++) {
    pinMode(bot->pinsM[i], OUTPUT);
  }
  motor_init(bot->pinsM[0], bot->pinsM[1], bot->pinsM[2], bot->pinsM[3]);
  encoder_init(bot->encoderPins[0], bot->encoderPins[1], bot->encoderPins[2],
               bot->encoderPins[3]);
}

void bot_forward(Bot *bot, int speed) {
  motor_on(MOTOR_FORWARD, speed, MOTOR_FORWARD, speed);
}

void bot_reverse(Bot *bot, int speed) {
  motor_on(MOTOR_REVERSE, speed, MOTOR_REVERSE, speed);
}

void bot_left(Bot *bot, int speed) {
  motor_on(MOTOR_REVERSE, speed, MOTOR_FORWARD, speed);
}

void bot_right(Bot *bot, int speed) {
  motor_on(MOTOR_FORWARD, speed, MOTOR_REVERSE, speed);
}

void bot_stop(Bot *bot) { motor_off(); }

void bot_create(Bot *bot) {
  bot->pinsM[0] = 3;
  bot->pinsM[1] = 2;
  bot->pinsM[2] = 4;
  bot->pinsM[3] = 31;
  bot->encoderPins[0] = 28;
  bot->encoderPins[1] = 14;
  bot->encoderPins[2] = 37;
  bot->encoderPins[3] = 11;
  bot->init = bot_init;
  bot->forward = bot_forward;
  bot->reverse = bot_reverse;
  bot->left = bot_left;
  bot->right = bot_right;
  bot->stop = bot_stop;
}
