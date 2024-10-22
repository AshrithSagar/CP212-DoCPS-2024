#ifndef GPIO_H
#define GPIO_H
#include "gpio.h"
#endif // GPIO_H

#ifndef TIMER_H
#define TIMER_H
#include "timer.h"
#endif // TIMER_H

#define N 5

void displayInit(void);
void displayImage(const char image[N][N]);
void displayRefresh(void);
