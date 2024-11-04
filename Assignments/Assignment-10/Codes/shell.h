#ifndef SHELL_H
#define SHELL_H

#include "display.h"

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

void cmd_help(int argc, char *argv[]);
void cmd_display(int argc, char *argv[]);
void cmd_up(int argc, char *argv[]);
void cmd_down(int argc, char *argv[]);
void cmd_left(int argc, char *argv[]);
void cmd_right(int argc, char *argv[]);
void cmd_exit(int argc, char *argv[]);

#endif // SHELL_H
