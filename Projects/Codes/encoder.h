#ifndef ENCODER_H
#define ENCODER_H

#include "bot.h"

void encoder_init(StackBot *bot);
float encoder_speed(int pin);
void encoder_update(int event);

#endif // ENCODER_H
