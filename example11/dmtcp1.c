#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int
main(int argc, char *argv[])
{
  int count = 1;
  while (1) {
    printf("\n");
    open("dummy.txt", O_WRONLY | O_APPEND);
    printf(" %2d ", count++);
    fflush(stdout);
    sleep(2);
  }
  return 0;
}
