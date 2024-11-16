#include "bot.h"

int main() {
  StackBot bot;
  bot_create(&bot);
  bot.init(&bot);
  return 0;
}
