#ifndef DISPLAY_H
#define DISPLAY_H

#include "gpio.h"
#include "timer.h"

#define N 5

void displayInit(void);
void displayImage(int image[N][N]);
void displayRefresh(void);

#endif // DISPLAY_H
