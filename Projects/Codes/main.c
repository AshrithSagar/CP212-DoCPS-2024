#include "bot.h"
#include "encoder.h"

int main() {
  bot_init();
  while (1) {
    encoder_counter();
  }
  return 0;
}
