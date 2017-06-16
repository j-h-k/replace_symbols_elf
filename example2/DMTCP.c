#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
typedef void func(void);

#define debug 0

void foo_wrap__dmtcp_1();
void foo_wrap__dmtcp_2();
void foo_wrap__dmtcp_3();

void foo__dmtcp_plt() {
  // This is in essence what happens
  /*	static int i = 1;
          switch(i++) {
          case 1:
                  foo_wrap__dmtcp_1();
                  break;
          case 2:
                  foo_wrap__dmtcp_2();
                  break;
          case 3:
                  foo_wrap__dmtcp_3();
                  break;
          default:
                  return;
          }
  */
  static int initialized = 0;
  static int counter = 0;
  static int numOfWrappers = 0;
  static long int addrs[100] = {0};

  if (!initialized) {
    char *string = malloc(sizeof(char) * 1000);
    char *filename = "./addrs/foo_wrap__dmtcp_*.addr";
    int fd = open(filename, O_RDONLY);
    char *token;

    if (fd == -1) {
      printf("*** *** NO FILE\n");
      exit(1);
    }

    read(fd, string, sizeof(char) * 1000);

    while ((token = strsep(&string, ",")) != NULL)
      if (token[0] != '\0') {
        addrs[numOfWrappers++] = strtol(token, NULL, 16);
        if (debug)
          printf("\t%ld\n", addrs[numOfWrappers - 1]);
      }
    free(string);
    initialized = 1;
  }
  if (counter < numOfWrappers) {
    ((func *)addrs[counter++])();
  }
}
