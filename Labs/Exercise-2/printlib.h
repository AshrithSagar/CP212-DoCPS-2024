#include <stdio.h>

// Already defined in stdio.h
// #define BUFSIZ 4096
// #define EOF -1

char mybuf[BUFSIZ];
int myindex;

int myputchar(int c);
int myputs(const char *s);
int myputd(int d);
int myputx(int d);
int myputf(float f);
