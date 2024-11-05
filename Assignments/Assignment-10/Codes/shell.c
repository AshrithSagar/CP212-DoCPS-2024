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

// Scroll the picture up by one row
void scroll_up() {
  int temp[N];
  // Save the first row for wrapping around
  memcpy(temp, picture[0], N * sizeof(int));

  // Shift all rows up
  for (int i = 1; i < N; i++) {
    memcpy(picture[i - 1], picture[i], N * sizeof(int));
  }

  // Wrap the first row to the last row
  memcpy(picture[N - 1], temp, N * sizeof(int));

  displayImage(picture);
}

// Scroll the picture down by one row
void scroll_down() {
  int temp[N];
  // Save the last row for wrapping around
  memcpy(temp, picture[N - 1], N * sizeof(int));

  // Shift all rows down
  for (int i = N - 2; i >= 0; i--) {
    memcpy(picture[i + 1], picture[i], N * sizeof(int));
  }

  // Wrap the last row to the first row
  memcpy(picture[0], temp, N * sizeof(int));

  displayImage(picture);
}

// Scroll the picture left by one column
void scroll_left() {
  int temp[N];
  // Save the first column for wrapping around
  for (int i = 0; i < N; i++) {
    temp[i] = picture[i][0];
  }

  // Shift all columns left
  for (int i = 0; i < N; i++) {
    for (int j = 1; j < N; j++) {
      picture[i][j - 1] = picture[i][j];
    }
  }

  // Wrap the first column to the last column
  for (int i = 0; i < N; i++) {
    picture[i][N - 1] = temp[i];
  }

  displayImage(picture);
}

// Scroll the picture right by one column
void scroll_right() {
  int temp[N];
  // Save the last column for wrapping around
  for (int i = 0; i < N; i++) {
    temp[i] = picture[i][N - 1];
  }

  // Shift all columns right
  for (int i = 0; i < N; i++) {
    for (int j = N - 2; j >= 0; j--) {
      picture[i][j + 1] = picture[i][j];
    }
  }

  // Wrap the last column to the first column
  for (int i = 0; i < N; i++) {
    picture[i][0] = temp[i];
  }

  displayImage(picture);
}

void cmd_up(int argc, char *argv[]) {
  for (int i = 0; i < N; i++) {
    scroll_up();
  }
  myprintf("Scrolled up:\r\n");
}

void cmd_down(int argc, char *argv[]) {
  for (int i = 0; i < N; i++) {
    scroll_down();
  }
  myprintf("Scrolled down:\r\n");
}

void cmd_left(int argc, char *argv[]) {
  for (int i = 0; i < N; i++) {
    scroll_left();
  }
  myprintf("Scrolled left:\r\n");
}

void cmd_right(int argc, char *argv[]) {
  for (int i = 0; i < N; i++) {
    scroll_right();
  }
  myprintf("Scrolled right:\r\n");
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
