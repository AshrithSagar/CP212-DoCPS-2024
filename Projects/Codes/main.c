#include "bot.h"

int main() {
  StackBot bot;
  bot_create(&bot);
  bot.init(&bot);
  bot.forward(&bot, 50);
  return 0;
}
