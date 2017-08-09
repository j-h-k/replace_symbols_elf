#include <stdio.h>
#ifndef _POSIX_SOURCE
# define _POSIX_SOURCE 2
#endif

#define _POSIX_C_SOURCE 199309L

#include <signal.h>

int main()
{
  rt_sigaction(0, NULL, NULL);
  return 0;
}
