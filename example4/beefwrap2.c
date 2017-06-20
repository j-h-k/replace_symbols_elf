#include <stdio.h>
void * dlsym();

void beef_wrap(char *cptr) {
  printf("Beef_wrap2 got: %c\n", *cptr);
  void (*fptr)(char*);
  void *handle = NULL;
  fptr = dlsym(handle, "beef");
  *cptr = *cptr + 1;
  (*fptr)(cptr);
  printf("Return from Beef_wrap2\n");
}
