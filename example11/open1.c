#define _GNU_SOURCE
#include <dlfcn.h>
#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>
#include "DMTCP.h"
#include "lib1.h"

int 
open(const char * pathname, int flags)
{
  printf("OPEN 1:::\n");
  fflush(stdout);
  return NEXT_FNC(open)(pathname, flags);
}
