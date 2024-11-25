/* This function computes a polynomial y = sum(Ci * x^i) for i = 0 to N. */

#include <math.h>
#include <stdio.h>

#define N 4
const int c[N] = {1234, 5678, 0x9ABC, 0xDEF0};

double poly(double x) {
  double y = 0.0;

  for (int i = 0; i < N; i++)
    y += c[i] * pow(x, i);

#ifdef TEST
  printf("y = %f, x = %f\n", y, x);
#endif

  return y;
}
