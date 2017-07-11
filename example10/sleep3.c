#define _GNU_SOURCE
#include <dlfcn.h>
#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>
#include "DMTCP.h"

static int plugin_id = 3;

unsigned int
sleep(unsigned int seconds)
{
  printf("(sleep3: "); printf(" ... ");
  unsigned int result = NEXT_FNC(sleep)(seconds);
  printf(") ");

  return result;
}
