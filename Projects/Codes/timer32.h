#ifndef TIMER32_H
#define TIMER32_H

#include "nrf52833.h"

void timer32_init(void);
unsigned long timer32_read(void);

#endif // TIMER32_H
