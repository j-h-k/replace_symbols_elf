#define _GNU_SOURCE
#include <dlfcn.h>
#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>
//#include "dmtcp.h"
#define NEXT_FNC(func)                                                       \
  ({                                                                         \
    static __typeof__(&func)_real_ ## func = (__typeof__(&func)) - 1;        \
    if (_real_ ## func == (__typeof__(&func)) - 1) {                         \
      _real_ ## func = (__typeof__(&func)) dlsym(RTLD_NEXT, # func);         \
    }                                                                        \
    _real_ ## func;                                                          \
  })

    /*if (_real_ ## func == (__typeof__(&func)) - 1) {                         \
      _real_ ## func = (__typeof__(&func)) dlsym(RTLD_NEXT, # func);         \
    } */                                                                       \
//__attribute__((used)) extern unsigned int sleep(unsigned int);

void
print_time();
/*{
  struct timeval val;

  gettimeofday(&val, NULL);
  printf("%ld %ld", (long)val.tv_sec, (long)val.tv_usec);
}*/

unsigned int
sleep(unsigned int seconds)
{
  printf("sleep1: "); print_time(); printf(" ... ");
  unsigned int result = NEXT_FNC(sleep)(seconds);
  print_time(); printf("\n");

  return result;
}

static void
checkpoint()
{
  printf("\n*** The plugin %s is being called before checkpointing. ***\n",
         __FILE__);
}

static void
resume()
{
  printf("*** The plugin %s has now been checkpointed. ***\n", __FILE__);
}

/*static DmtcpBarrier barriers[] = {
  { DMTCP_GLOBAL_BARRIER_PRE_CKPT, checkpoint, "checkpoint" },
  { DMTCP_GLOBAL_BARRIER_RESUME, resume, "resume" }
};

DmtcpPluginDescriptor_t sleep1_plugin = {
  DMTCP_PLUGIN_API_VERSION,
  DMTCP_PACKAGE_VERSION,
  "sleep1",
  "DMTCP",
  "dmtcp@ccs.neu.edu",
  "Sleep1 plugin",
  DMTCP_DECL_BARRIERS(barriers),
  NULL
};

DMTCP_DECL_PLUGIN(sleep1_plugin);*/
