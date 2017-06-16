#include <stdio.h>
void foo();

void foo_wrap() {
  printf("From wrapfile: 3\n");
  foo();
  printf("Return wrapfile: 3\n");
}
