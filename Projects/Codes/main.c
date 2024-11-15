#include "bot.h"
#include "encoder.h"

int main() {
  Bot bot;
  bot_create(&bot);
  bot.init(&bot);
  while (1) {
    encoder_counter();
  }
  return 0;
}
