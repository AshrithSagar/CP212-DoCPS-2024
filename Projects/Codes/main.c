#include "bot.h"

int main() {
  MotorPins motorPins = {3, 2, 4, 31};
  EncoderPins encoderPins = {28, 14, 37, 11};
  struct StackBot *bot = configStackBot(motorPins, encoderPins);

  bot->init(bot);
  bot->forward(bot, 20);
}
