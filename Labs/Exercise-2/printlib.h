#ifndef PRINTLIB_H // Include Guard: Prevent multiple inclusions
#define PRINTLIB_H

#include <stdio.h> // For BUFSIZ and EOF
// #define	BUFSIZ	1024
// #define	EOF	(-1)

// Buffer to which the output is written to
char mybuf[BUFSIZ];
int myindex;

// Function prototypes
int myputchar(int c);
int myputs(const char *s);
int myputd(int d);
int myputx(int d);
int myputf(float f);

#endif // PRINTLIB_H
