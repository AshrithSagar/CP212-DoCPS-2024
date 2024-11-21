#include "bot.h"
#include "encoder.h"
#include "gpio.h"
#include "motor.h"
#include "uart.h"
#include <stdlib.h>

void bot_init(StackBot *bot) {
  pinMode(bot->motorPins.M1A, OUTPUT, PULL_NONE);
  pinMode(bot->motorPins.M1B, OUTPUT, PULL_NONE);
  pinMode(bot->motorPins.M2A, OUTPUT, PULL_NONE);
  pinMode(bot->motorPins.M2B, OUTPUT, PULL_NONE);

  uart_init();
  motor_init(bot->motorPins.M1A, bot->motorPins.M1B, bot->motorPins.M2A,
             bot->motorPins.M2B);
  encoder_init(bot->encoderPins.M1E1, bot->encoderPins.M1E2,
               bot->encoderPins.M2E1, bot->encoderPins.M2E2);
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

StackBot *configStackBot(MotorPins motorPins, EncoderPins encoderPins) {
  StackBot *bot = (StackBot *)malloc(sizeof(StackBot));
  bot->motorPins = motorPins;
  bot->encoderPins = encoderPins;
  bot->init = bot_init;
  bot->forward = bot_forward;
  bot->reverse = bot_reverse;
  bot->left = bot_left;
  bot->right = bot_right;
  bot->stop = bot_stop;
  return bot;
}
