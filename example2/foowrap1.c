#include <stdio.h>
void foo();

void foo_wrap() {
  printf("From wrapfile: 1\n");
  foo();
  printf("Return wrapfile: 1\n");
}
