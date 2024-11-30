#include "bot.h"
#include "encoder.h"
#include "motor.h"
#include "printlib.h"
#include "radio.h"
#include "uart.h"
#include <stdlib.h>

StackBot *botG;

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
    if (bot->state != STILL)
      bot_stop(bot);
    break;
  default:
    bot_stop(bot);
    break;
  }
  bot->state = direction;
  bot->speed = speed;
}

void bot_uart_control(StackBot *bot, int speed) {
  bot->speed = speed;
  char input[3];

  const struct {
    char key[3];
    Direction direction;
  } KEY_MAP[] = {
      {"\x1B[A", FORWARD}, // Up arrow
      {"\x1B[B", REVERSE}, // Down arrow
      {"\x1B[C", RIGHT},   // Right arrow
      {"\x1B[D", LEFT},    // Left arrow
      {" ", STILL},        // Spacebar
  };

  while (1) {
    input[0] = uart_getc();
    if (input[0] == '\x1B') {
      input[1] = uart_getc();
      if (input[1] == '[') {
        input[2] = uart_getc();
      }
    }

    if (input[0] >= '0' && input[0] <= '9') {
      bot->speed = (input[0] == '0') ? 100 : (input[0] - '0') * 10;
      bot_move(bot, bot->state, bot->speed);
      myprintf("\nSpeed set to %d%%\n", bot->speed);
    }

    for (int i = 0; i < sizeof(KEY_MAP) / sizeof(KEY_MAP[0]); i++) {
      if ((input[0] == KEY_MAP[i].key[0] && input[1] == KEY_MAP[i].key[1] &&
           input[2] == KEY_MAP[i].key[2]) ||
          (input[0] == KEY_MAP[i].key[0] && KEY_MAP[i].key[0] == ' ')) {
        bot_move(bot, KEY_MAP[i].direction, bot->speed);
        break;
      }
    }

    input[0] = input[1] = input[2] = 0;
  }
}

void radio_rx_callback(const char buf[], unsigned int n) {
  if (n != 1) {
    return;
  }
  char command = buf[0];
  switch (command) {
  case 'w':
    bot_move(botG, FORWARD, botG->speed);
    break;
  case 's':
    bot_move(botG, REVERSE, botG->speed);
    break;
  case 'a':
    bot_move(botG, LEFT, botG->speed);
    break;
  case 'd':
    bot_move(botG, RIGHT, botG->speed);
    break;
  case ' ':
    bot_move(botG, STILL, botG->speed);
    break;
  default:
    break;
  }
}

void bot_radio_control(StackBot *bot, int speed) {
  bot->speed = speed;
  char input[3];

  const struct {
    char key[3];
    Direction direction;
  } KEY_MAP[] = {
      {"w", FORWARD}, // W key
      {"s", REVERSE}, // S key
      {"d", RIGHT},   // D key
      {"a", LEFT},    // A key
      {" ", STILL},   // Spacebar
  };

  radio_init(radio_rx_callback);
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
  botG = bot;
  return bot;
}
