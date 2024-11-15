#ifndef BOT_H
#define BOT_H

#include "encoder.h"
#include "gpio.h"
#include "motor.h"

void bot_init(void);
void bot_forward(int speed);
void bot_reverse(int speed);
void bot_left(int speed);
void bot_right(int speed);
void bot_stop(void);

#endif // BOT_H
