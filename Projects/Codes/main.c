#include "bot.h"
#include "encoder.h"

int main() {
  bot_init();
  encoder_init();
  encoder_counter();
  return 0;
}
