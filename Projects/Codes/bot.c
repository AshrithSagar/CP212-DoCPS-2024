/**
 * @file bot.c
 * @brief Implementation of the StackBot control functions.
 *
 * This file contains the implementation of functions to initialize, control,
 * and manage the state of a StackBot robot. It includes functions for motor
 * control, UART communication, and bot configuration.
 */

#include "bot.h"
#include "encoder.h"
#include "motor.h"
#include "printlib.h"
#include "uart.h"
#include <stdlib.h>

/**
 * @brief Initializes the StackBot.
 *
 * This function initializes the UART, motor, and encoder for the StackBot.
 * It also prints a message indicating that the bot has been initialized.
 *
 * @param bot Pointer to the StackBot structure.
 */
void bot_init(StackBot *bot);

/**
 * @brief Stops the StackBot.
 *
 * This function sets the bot's state to STILL and turns off the motor.
 *
 * @param bot Pointer to the StackBot structure.
 */
void bot_stop(StackBot *bot);

/**
 * @brief Moves the StackBot in a specified direction at a specified speed.
 *
 * This function controls the movement of the StackBot based on the given
 * direction and speed. It updates the bot's state and speed accordingly.
 *
 * @param bot Pointer to the StackBot structure.
 * @param direction The direction to move the bot (FORWARD, REVERSE, LEFT,
 * RIGHT, STILL).
 * @param speed The speed at which to move the bot (0-100).
 */
void bot_move(StackBot *bot, Direction direction, int speed);

/**
 * @brief Controls the StackBot using UART input.
 *
 * This function allows the StackBot to be controlled via UART input. It
 * interprets arrow keys for direction and numeric keys for speed.
 *
 * @param bot Pointer to the StackBot structure.
 * @param speed Initial speed of the bot.
 */
void bot_uart_control(StackBot *bot, int speed);

/**
 * @brief Configures and allocates memory for a new StackBot.
 *
 * This function allocates memory for a new StackBot structure and initializes
 * its motor and encoder pins. It also sets the initial state and assigns
 * function pointers for bot operations.
 *
 * @param motorPins Motor pin configuration.
 * @param encoderPins Encoder pin configuration.
 * @return Pointer to the newly configured StackBot structure.
 */
StackBot *configStackBot(MotorPins motorPins, EncoderPins encoderPins);

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
