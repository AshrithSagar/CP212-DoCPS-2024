int linear(int x);

#define N 4
int x_array[] = {2, 5, -3, 8};
int y_array[N];

int main(void) {
  int i;

  for (i = 0; i < N; i++)
    y_array[i] = linear(x_array[i]);

  while (1) // keep looping to remain in main()
    ;

  return 0;
}
