#ifndef SHELL_H
#define SHELL_H

#include "display.h"
#include "printlib.h"
#include "timer.h"
#include "uart.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ARGS 10
#define MAX_COMMANDS 7

void shellInit(void);

#endif // SHELL_H
