#ifndef MOTOR_H
#define MOTOR_H

#include "nrf52833.h"
#include <stdint.h>

void motor_init(int M1A, int M1B, int M2A, int M2B);
void motor_on(int dirA, int dutyA, int dirB, int dutyB);
void motor_off(void);
enum { MOTOR_FORWARD, MOTOR_REVERSE };

#endif /* MOTOR_H */
