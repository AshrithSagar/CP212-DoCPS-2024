#ifndef DISPLAY_H
#define DISPLAY_H

#define N 5

void displayInit(void);
void displayImage(const char image[N][N]);

void naiveDelay(int ms);

#endif // DISPLAY_H
