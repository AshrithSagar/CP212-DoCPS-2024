#include "encoder.h"

#define ENC1 17

void encoder_init(void) { pinMode(ENC1, OUTPUT); }

void encoder_counter(void) {
  static int counter = 0;
  int current = digitalRead(ENC1);

  if (current == HIGH) {
    counter++;
  }
}
