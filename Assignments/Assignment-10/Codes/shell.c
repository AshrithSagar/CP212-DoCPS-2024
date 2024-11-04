#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ARGS 10
#define MAX_COMMANDS 3

void cmd_hello(int argc, char *argv[]);
void cmd_add(int argc, char *argv[]);
void cmd_exit(int argc, char *argv[]);

typedef struct {
  const char *name;
  void (*func)(int, char **);
} Command;

Command commands[] = {
    {"hello", cmd_hello},
    {"add", cmd_add},
    {"exit", cmd_exit},
};

int parse_command(char *line, int *argc, char *argv[]) {
  char *token = strtok(line, " \t\n");
  *argc = 0;
  while (token != NULL && *argc < MAX_ARGS) {
    argv[(*argc)++] = token;
    token = strtok(NULL, " \t\n");
  }
  argv[*argc] = NULL;
  return *argc;
}

void execute_command(int argc, char *argv[]) {
  int found = 0;

  if (argc > 0) {
    for (int i = 0; i < MAX_COMMANDS; i++) {
      if (strcmp(argv[0], commands[i].name) == 0) {
        commands[i].func(argc, argv);
        found = 1;
        break;
      }
    }
    if (!found) {
      printf("Unknown command: %s\n", argv[0]);
    }
  }
}

void cmd_hello(int argc, char *argv[]) { printf("Hello, World!\n"); }

void cmd_add(int argc, char *argv[]) {
  if (argc < 3) {
    printf("Usage: add <num1> <num2>\n");
    return;
  }
  int num1 = atoi(argv[1]);
  int num2 = atoi(argv[2]);
  printf("Result: %d\n", num1 + num2);
}

void cmd_exit(int argc, char *argv[]) {
  printf("Exiting...\n");
  exit(0);
}

int main() {
  char line[100];
  char *argv[MAX_ARGS];
  int argc;

  while (1) {
    printf("> ");
    if (fgets(line, sizeof(line), stdin) == NULL) {
      break;
    }

    parse_command(line, &argc, argv);
    execute_command(argc, argv);
  }

  return 0;
}
