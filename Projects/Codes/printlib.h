#ifndef PRINTLIB_H
#define PRINTLIB_H

#include "uart.h"

int myputchar(int c);
int myputs(const char *s);
int myputd(int d);
int myputx(int d);
int myputf(float f);
int myprintf(const char *format, ...);

#endif // PRINTLIB_H
