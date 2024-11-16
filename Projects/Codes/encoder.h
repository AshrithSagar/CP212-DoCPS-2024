#ifndef ENCODER_H
#define ENCODER_H

#include "gpio.h"
#include "printlib.h"
#include "timer32.h"
#include "uart.h"

void encoder_init(int M1E1, int M1E2, int M2E1, int M2E2);
void encoder_counter(void);

#endif // ENCODER_H
