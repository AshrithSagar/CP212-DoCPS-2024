/* This function computes a polynomial y = sum(Ci * x^i) for i = 0 to N.

#define N 4
const c[4] = {1234, 5678, 9ABC, DEF0};

double poly(double x)
{
    int y;

    for (i = 0; i <= N; i++)
        y += c[i] * pow(x, i);

#ifdef TEST
    printff("y = %f, x = %f\n", x, y);
#endif

    return y;
}
