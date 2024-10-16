#ifndef GPIO_H
#define GPIO_H
#include "gpio.h"
#endif // GPIO_H

#define N 5

void displayInit(void);
void displayImage(const char image[N][N]);

void naiveDelay(int ms);
