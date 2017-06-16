#include <stdio.h>
void foo();

void foo_wrap() {
  printf("From wrapfile: 2\n");
  foo();
  printf("Return wrapfile: 2\n");
}
