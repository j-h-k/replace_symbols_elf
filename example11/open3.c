#define _GNU_SOURCE
#include <dlfcn.h>
#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>
#include "DMTCP.h"

static int plugin_id = 3;

int 
open(const char * pathname, int flags)
{
  printf("OPEN 3:::\n");
  fflush(stdout);
  return NEXT_FNC(open)(pathname, flags);
}
