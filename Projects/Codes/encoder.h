#ifndef ENCODER_H
#define ENCODER_H

#include "gpio.h"
#include "nrf52833.h"
#include "printlib.h"
#include "timer32.h"
#include "uart.h"
#include <stdint.h>

void encoder_init(int M1E1, int M1E2, int M2E1, int M2E2);
float encoder_speed(int pin);
void encoder_update(int event);

#endif // ENCODER_H
