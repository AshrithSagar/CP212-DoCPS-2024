#include "display.h"

char pic[N][N] = {{0, 1, 0, 1, 0},
                  {1, 0, 1, 0, 1},
                  {0, 1, 0, 1, 0},
                  {1, 0, 1, 0, 1},
                  {0, 1, 0, 1, 0}};

int main(void) {
  displayInit();

  while (1)
    display(pic);

  return 0;
}
