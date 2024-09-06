#include "string.h"

int len1, len2;
long testmem[10];

char src[] = "Welcome to mystrcpy.";
char dest[32]; // sufficiently large to hold the copy

int main(void) {
  len1 = mystrlen("Hi!");
  len2 = mystrlen("Hello, world!");

  mystrcpy(dest, src);

  testmem[0] = mystrcmp("Apple", "Mango");
  testmem[1] = mystrcmp("Mango", "Apple");
  testmem[2] = mystrcmp("Bang", "Bangalore");
  testmem[3] = mystrcmp("Bangalore", "Bang");
  testmem[4] = mystrcmp("Rose", "Rose");

  return 0;
}
