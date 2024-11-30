#include "bot.h"

int main() {
  MotorPins motorPins = {.M1A = 3, .M1B = 2, .M2A = 4, .M2B = 31};
  EncoderPins encoderPins = {.M1E1 = 28, .M1E2 = 14, .M2E1 = 37, .M2E2 = 11};
  ButtonPins buttonPins = {.btnA = 14, .btnB = 23};
  StackBot *bot = configStackBot(motorPins, encoderPins, buttonPins);

  bot_init(bot);
  bot_button_control(bot, 20);
}
