#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int main()
{
  int i = 0;
  printf("main started~!~!~!\n");
  while (1) {
    printf("%d ", i++);
    fflush(stdout);
    sleep(1);
  }
  return 0;
}
