#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ARGS 10
#define MAX_COMMANDS 7

void cmd_help(int argc, char *argv[]);
void cmd_display(int argc, char *argv[]);
void cmd_up(int argc, char *argv[]);
void cmd_down(int argc, char *argv[]);
void cmd_left(int argc, char *argv[]);
void cmd_right(int argc, char *argv[]);
void cmd_exit(int argc, char *argv[]);

typedef struct {
  const char *name;
  void (*func)(int, char **);
} Command;

Command commands[] = {
    {"help", cmd_help}, {"display", cmd_display}, {"up", cmd_up},
    {"down", cmd_down}, {"left", cmd_left},       {"right", cmd_right},
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
void cmd_help(int argc, char *argv[]) {
  printf("Available commands:\n");
  for (int i = 0; i < MAX_COMMANDS; i++) {
    printf(" - %s\n", commands[i].name);
  }
}

#define N 5
int picture[N][N] = {0};

void cmd_display(int argc, char *argv[]) {
  if (argc != 6) {
    printf("Usage: display <row1> <row2> <row3> <row4> <row5>\n");
    return;
  }

  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      picture[i][j] = argv[i + 1][j] - '0'; // Convert char to int
    }
  }

  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      printf("%d ", picture[i][j]);
    }
    printf("\n");
  }
}

void rotate_left() {
  int temp[N][N];
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      temp[i][j] = picture[j][N - 1 - i];
    }
  }
  memcpy(picture, temp, sizeof(picture));
}

void rotate_right() {
  int temp[N][N];
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      temp[i][j] = picture[N - 1 - j][i];
    }
  }
  memcpy(picture, temp, sizeof(picture));
}

void cmd_up(int argc, char *argv[]) {
  for (int i = 0; i < 5; i++) {
    rotate_left();
  }
  printf("Rotated up:\n");
  cmd_display(6, (char *[]){NULL, "0", "0", "0", "0", "0"});
}

void cmd_down(int argc, char *argv[]) {
  for (int i = 0; i < 5; i++) {
    rotate_right();
  }
  printf("Rotated down:\n");
  cmd_display(6, (char *[]){NULL, "0", "0", "0", "0", "0"});
}

void cmd_left(int argc, char *argv[]) {
  for (int i = 0; i < 5; i++) {
    rotate_left();
  }
  printf("Rotated left:\n");
  cmd_display(6, (char *[]){NULL, "0", "0", "0", "0", "0"});
}

void cmd_right(int argc, char *argv[]) {
  for (int i = 0; i < 5; i++) {
    rotate_right();
  }
  printf("Rotated right:\n");
  cmd_display(6, (char *[]){NULL, "0", "0", "0", "0", "0"});
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
