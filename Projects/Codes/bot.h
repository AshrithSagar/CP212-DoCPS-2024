#ifndef BOT_H
#define BOT_H

#include "encoder.h"
#include "gpio.h"
#include "motor.h"

typedef struct Bot {
  int pinsM[4];
  int encoderPins[4];
  void (*init)(struct Bot *);
  void (*forward)(struct Bot *, int);
  void (*reverse)(struct Bot *, int);
  void (*left)(struct Bot *, int);
  void (*right)(struct Bot *, int);
  void (*stop)(struct Bot *);
} Bot;
void bot_create(Bot *bot);
void bot_init(Bot *bot);
void bot_forward(Bot *bot, int speed);
void bot_reverse(Bot *bot, int speed);
void bot_left(Bot *bot, int speed);
void bot_right(Bot *bot, int speed);
void bot_stop(Bot *bot);

#endif // BOT_H
