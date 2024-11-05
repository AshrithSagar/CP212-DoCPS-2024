#include "shell.h"
#include "display.h"
#include "uart.h"

int picture[N][N] = {0};

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
      myprintf("Unknown command: %s\r\n", argv[0]);
    }
  }
}
void cmd_help(int argc, char *argv[]) {
  myprintf("Available commands:\r\n");
  for (int i = 0; i < MAX_COMMANDS; i++) {
    myprintf(" - %s\r\n", commands[i].name);
  }
}

void cmd_display(int argc, char *argv[]) {
  if (argc != N + 1) {
    myprintf("Usage: display <row1> <row2> <row3> <row4> <row5>\r\n");
    return;
  }

  for (int i = 0; i < N; i++) {
    if (strlen(argv[i + 1]) != N) {
      myprintf("Each row must contain exactly %d bits (0 or 1).\r\n", N);
      return;
    }

    for (int j = 0; j < N; j++) {
      if (argv[i + 1][j] != '0' && argv[i + 1][j] != '1') {
        myprintf("Invalid bit found: %c. Only 0 or 1 is allowed.\r\n",
                 argv[i + 1][j]);
        return;
      }
      picture[i][j] = argv[i + 1][j] - '0'; // Convert char to int
    }
  }

  displayImage(picture);

  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      myprintf("%d ", picture[i][j]);
    }
    myprintf("\r\n");
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
  myprintf("Rotated up:\r\n");
  cmd_display(6, (char *[]){NULL, "0", "0", "0", "0", "0"});
}

void cmd_down(int argc, char *argv[]) {
  for (int i = 0; i < 5; i++) {
    rotate_right();
  }
  myprintf("Rotated down:\r\n");
  cmd_display(6, (char *[]){NULL, "0", "0", "0", "0", "0"});
}

void cmd_left(int argc, char *argv[]) {
  for (int i = 0; i < 5; i++) {
    rotate_left();
  }
  myprintf("Rotated left:\r\n");
  cmd_display(6, (char *[]){NULL, "0", "0", "0", "0", "0"});
}

void cmd_right(int argc, char *argv[]) {
  for (int i = 0; i < 5; i++) {
    rotate_right();
  }
  myprintf("Rotated right:\r\n");
  cmd_display(6, (char *[]){NULL, "0", "0", "0", "0", "0"});
}

void cmd_exit(int argc, char *argv[]) {
  myprintf("Exiting...\r\n");
  exit(0);
}

void shellInit(void) {
  char line[100];
  char *argv[MAX_ARGS];
  int argc;

  myprintf("Welcome to the shell! Enter a command to start ...\r\n");

  while (1) {
    myprintf("> ");

    if (uart_fgets(line, sizeof(line)) == NULL) {
      myprintf("Error reading input.\r\n");
      break;
    }

    // Skip empty inputs
    if (line[0] == '\0') {
      continue;
    }

    parse_command(line, &argc, argv);
    execute_command(argc, argv);
  }
}
