#include "bot.h"

int main() {
  MotorPins motorPins = {.M1A = 3, .M1B = 2, .M2A = 4, .M2B = 31};
  EncoderPins encoderPins = {.M1E1 = 28, .M1E2 = 14, .M2E1 = 37, .M2E2 = 11};
  StackBot *bot = configStackBot(motorPins, encoderPins);

  bot->init(bot);
  bot->uart_control(bot, 20);
}
