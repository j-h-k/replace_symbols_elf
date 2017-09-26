#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int main()
{
  printf("main started~!~!~!\n");
  fflush(stdout);
  close(2);
  return 0;
}
