#include "bot.h"
#include "gpio.h"
#include "motor.h"
#include "printlib.h"
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

  myprintf("\nBot initialized\n");
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

void bot_uart_control(StackBot *bot) {
  char input;
  while (1) {
    input = uart_getc();
    switch (input) {
    case 'w': // Forward
      bot->move(bot, FORWARD, 25);
      break;
    case 's': // Reverse
      bot->move(bot, REVERSE, 25);
      break;
    case 'a': // Left
      bot->move(bot, LEFT, 25);
      break;
    case 'd': // Right
      bot->move(bot, RIGHT, 25);
      break;
    case 'x': // Stop
      bot->stop(bot);
      break;
    default:
      break;
    }
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
  bot->uart_control = bot_uart_control;
  return bot;
}
