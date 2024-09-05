#include "string.h"
#include <stdio.h>

int main(void) {
  char mystring[] = "Hello World!";
  char newstring[BUFSIZ];

  printf("%d\n", mystrlen(mystring));
  printf("%s\n", mystrcpy(newstring, mystring));
  printf("%d", mystrcmp(mystring, "Hello world?"));

  return 0;
}
