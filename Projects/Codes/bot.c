#include "bot.h"
#include "encoder.h"
#include "motor.h"
#include "printlib.h"
#include "uart.h"
#include <stdlib.h>

void bot_init(StackBot *bot) {
  uart_init();
  motor_init(bot);
  encoder_init(bot);

  myprintf("\nBot initialized\n");
}

void bot_stop(StackBot *bot) {
  bot->state = STILL;
  motor_off();
}

void bot_move(StackBot *bot, Direction direction, int speed) {
  bot->state = direction;
  bot->speed = speed;
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
  case STILL:
    bot_stop(bot);
    break;
  default:
    bot_stop(bot);
    break;
  }
}

void bot_uart_control(StackBot *bot, int speed) {
  bot->speed = speed;
  char input;

  const struct {
    char key;
    Direction direction;
  } KEY_MAP[] = {
      {'w', FORWARD}, {'s', REVERSE}, {'a', LEFT}, {'d', RIGHT}, {'x', STILL},
  };

  while (1) {
    input = uart_getc();

    if (input >= '0' && input <= '9') {
      bot->speed = (input == '0') ? 100 : (input - '0') * 10;
      bot_move(bot, bot->state, bot->speed);
      myprintf("\nSpeed set to %d%%\n", bot->speed);
    }

    for (int i = 0; i < numStates; i++) {
      if (input == KEY_MAP[i].key) {
        bot_move(bot, KEY_MAP[i].direction, bot->speed);
        break;
      }
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
