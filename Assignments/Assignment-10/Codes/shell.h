#ifndef SHELL_H
#define SHELL_H

#include "display.h"
#include "printlib.h"

#ifndef STDIO_H
#define STDIO_H
#include <stdio.h>
#endif // STDIO_H

#ifndef STDLIB_H
#define STDLIB_H
#include <stdlib.h>
#endif // STDLIB_H

#ifndef STRING_H
#define STRING_H
#include <string.h>
#endif // STRING_H

#define MAX_ARGS 10
#define MAX_COMMANDS 7

void shellInit(void);

#endif // SHELL_H
