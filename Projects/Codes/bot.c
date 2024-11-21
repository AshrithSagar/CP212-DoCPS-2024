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

void bot_stop(StackBot *bot) {
  bot->state = STILL;
  motor_off();
}

void bot_move(StackBot *bot, Direction direction, int speed) {
  bot->state = direction;
  switch (direction) {
  case FORWARD:
    motor_on(MOTOR_FORWARD, speed, MOTOR_FORWARD, speed);
    break;
  case REVERSE:
    motor_on(MOTOR_REVERSE, speed, MOTOR_REVERSE, speed);
    break;
  case LEFT:
    motor_on(MOTOR_REVERSE, speed, MOTOR_FORWARD, speed);
    break;
  case RIGHT:
    motor_on(MOTOR_FORWARD, speed, MOTOR_REVERSE, speed);
    break;
  default:
    bot_stop(bot);
    break;
  }
}

StackBot *configStackBot(MotorPins motorPins, EncoderPins encoderPins) {
  StackBot *bot = (StackBot *)malloc(sizeof(StackBot));
  bot->motorPins = motorPins;
  bot->encoderPins = encoderPins;
  bot->state = STILL;
  bot->init = bot_init;
  bot->move = bot_move;
  bot->stop = bot_stop;
  return bot;
}
