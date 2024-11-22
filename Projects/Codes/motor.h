#ifndef MOTOR_H
#define MOTOR_H

#include "bot.h"

void motor_init(StackBot *bot);
void motor_on(MotorDirection dirA, int dutyA, MotorDirection dirB, int dutyB);
void motor_off(void);

#endif /* MOTOR_H */
