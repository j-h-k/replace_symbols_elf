#include <stdio.h>
void* dlsym();

int foo_wrap(int num1, int num2) {
  int res = 0;
  printf("From wrapfile: 2 got num1=%d num2=%d\n", num1, num2);
  int (*fptr)(int, int);
  void *handle = NULL;
  fptr = dlsym(handle, "foo");
  res = fptr(num1+1, num2+1);
  printf("Return wrapfile: 2\n");
  return res;
}
