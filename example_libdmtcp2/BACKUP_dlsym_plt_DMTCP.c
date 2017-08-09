#define _GNU_SOURCE
#define _XOPEN_SOURCE 600
#include "DMTCP.h"
static int plugin_id = 0;
#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <signal.h>
#include <pthread.h>
#include <features.h>
#include <syslog.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <sys/wait.h>
#include <dirent.h>
#define SETUP_FPTR(symbol) void * __fptr = (void *) NEXT_FNC_S_DEFAULT(symbol)
#define DELETE_CALL_FRAME() \
  asm ("mov %%rbp, %%r11\n\t" \
        "sub %%rsp, %%r11\n\t" \
        "add %%r11, %%rsp\n\t" \
        "pop %%rbp\n\t" \
        "jmp *%0" \
        : \
        : "a" (__fptr) \
        : )
//extern void * dmtcp_sdlsym(char *, void *, char *, long int *);
//extern void * dmtcp_sdlsym(char *, void *, int, long int *);
long int signaladdrs[100];
void signal__dmtcp_plt(){
  SETUP_FPTR(signal);
  DELETE_CALL_FRAME();
}
long int sigactionaddrs[100];
void sigaction__dmtcp_plt(){
  SETUP_FPTR(sigaction);
  DELETE_CALL_FRAME();
}
//KJ long int rt_sigactionaddrs[100];
//KJ void rt_sigaction__dmtcp_plt(){
//KJ   SETUP_FPTR(rt_sigaction);
//KJ   DELETE_CALL_FRAME();
//KJ }
//KJ long int sigvecaddrs[100];
//KJ void sigvec__dmtcp_plt(){
//KJ   SETUP_FPTR(sigvec);
//KJ   DELETE_CALL_FRAME();
//KJ }
long int sigblockaddrs[100];
void sigblock__dmtcp_plt(){
  SETUP_FPTR(sigblock);
  DELETE_CALL_FRAME();
}
long int sigsetmaskaddrs[100];
void sigsetmask__dmtcp_plt(){
  SETUP_FPTR(sigsetmask);
  DELETE_CALL_FRAME();
}
long int siggetmaskaddrs[100];
void siggetmask__dmtcp_plt(){
  SETUP_FPTR(siggetmask);
  DELETE_CALL_FRAME();
}
long int sigprocmaskaddrs[100];
void sigprocmask__dmtcp_plt(){
  SETUP_FPTR(sigprocmask);
  DELETE_CALL_FRAME();
}
//KJ long int rt_sigprocmaskaddrs[100];
//KJ void rt_sigprocmask__dmtcp_plt(){
//KJ   SETUP_FPTR(rt_sigprocmask);
//KJ   DELETE_CALL_FRAME();
//KJ }
long int sigsuspendaddrs[100];
void sigsuspend__dmtcp_plt(){
  SETUP_FPTR(sigsuspend);
  DELETE_CALL_FRAME();
}
long int sigholdaddrs[100];
void sighold__dmtcp_plt(){
  SETUP_FPTR(sighold);
  DELETE_CALL_FRAME();
}
long int sigignoreaddrs[100];
void sigignore__dmtcp_plt(){
  SETUP_FPTR(sigignore);
  DELETE_CALL_FRAME();
}
long int sigrelseaddrs[100];
void sigrelse__dmtcp_plt(){
  SETUP_FPTR(sigrelse);
  DELETE_CALL_FRAME();
}
//KJ long int __sigpauseaddrs[100];
//KJ void __sigpause__dmtcp_plt(){
//KJ   SETUP_FPTR(__sigpause);
//KJ   DELETE_CALL_FRAME();
//KJ }
long int sigpauseaddrs[100];
void sigpause__dmtcp_plt(){
  SETUP_FPTR(sigpause);
  DELETE_CALL_FRAME();
}
long int pthread_sigmaskaddrs[100];
void pthread_sigmask__dmtcp_plt(){
  SETUP_FPTR(pthread_sigmask);
  DELETE_CALL_FRAME();
}
long int sigwaitaddrs[100];
void sigwait__dmtcp_plt(){
  SETUP_FPTR(sigwait);
  DELETE_CALL_FRAME();
}
long int sigwaitinfoaddrs[100];
void sigwaitinfo__dmtcp_plt(){
  SETUP_FPTR(sigwaitinfo);
  DELETE_CALL_FRAME();
}
long int sigtimedwaitaddrs[100];
void sigtimedwait__dmtcp_plt(){
  SETUP_FPTR(sigtimedwait);
  DELETE_CALL_FRAME();
}
long int forkaddrs[100];
void fork__dmtcp_plt(){
  SETUP_FPTR(fork);
  DELETE_CALL_FRAME();
}
long int daemonaddrs[100];
void daemon__dmtcp_plt(){
  SETUP_FPTR(daemon);
  DELETE_CALL_FRAME();
}
long int vforkaddrs[100];
void vfork__dmtcp_plt(){
  SETUP_FPTR(vfork);
  DELETE_CALL_FRAME();
}
long int execveaddrs[100];
void execve__dmtcp_plt(){
  SETUP_FPTR(execve);
  DELETE_CALL_FRAME();
}
long int execvaddrs[100];
void execv__dmtcp_plt(){
  SETUP_FPTR(execv);
  DELETE_CALL_FRAME();
}
long int execvpaddrs[100];
void execvp__dmtcp_plt(){
  SETUP_FPTR(execvp);
  DELETE_CALL_FRAME();
}
long int execvpeaddrs[100];
void execvpe__dmtcp_plt(){
  SETUP_FPTR(execvpe);
  DELETE_CALL_FRAME();
}
long int fexecveaddrs[100];
void fexecve__dmtcp_plt(){
  SETUP_FPTR(fexecve);
  DELETE_CALL_FRAME();
}
long int execladdrs[100];
void execl__dmtcp_plt(){
  SETUP_FPTR(execl);
  DELETE_CALL_FRAME();
}
long int execlpaddrs[100];
void execlp__dmtcp_plt(){
  SETUP_FPTR(execlp);
  DELETE_CALL_FRAME();
}
long int execleaddrs[100];
void execle__dmtcp_plt(){
  SETUP_FPTR(execle);
  DELETE_CALL_FRAME();
}
long int systemaddrs[100];
void system__dmtcp_plt(){
  SETUP_FPTR(system);
  DELETE_CALL_FRAME();
}
long int exitaddrs[100];
void exit__dmtcp_plt(){
  SETUP_FPTR(exit);
  DELETE_CALL_FRAME();
}
long int closeaddrs[100];
void close__dmtcp_plt(){
  SETUP_FPTR(close);
  DELETE_CALL_FRAME();
}
long int fcloseaddrs[100];
void fclose__dmtcp_plt(){
  SETUP_FPTR(fclose);
  DELETE_CALL_FRAME();
}
long int closediraddrs[100];
void closedir__dmtcp_plt(){
  SETUP_FPTR(closedir);
  DELETE_CALL_FRAME();
}
long int dup2addrs[100];
void dup2__dmtcp_plt(){
  SETUP_FPTR(dup2);
  DELETE_CALL_FRAME();
}
long int pipeaddrs[100];
void pipe__dmtcp_plt(){
  SETUP_FPTR(pipe);
  DELETE_CALL_FRAME();
}
long int pipe2addrs[100];
void pipe2__dmtcp_plt(){
  SETUP_FPTR(pipe2);
  DELETE_CALL_FRAME();
}
long int waitaddrs[100];
void wait__dmtcp_plt(){
  SETUP_FPTR(wait);
  DELETE_CALL_FRAME();
}
long int waitpidaddrs[100];
void waitpid__dmtcp_plt(){
  SETUP_FPTR(waitpid);
  DELETE_CALL_FRAME();
}
long int wait3addrs[100];
void wait3__dmtcp_plt(){
  SETUP_FPTR(wait3);
  DELETE_CALL_FRAME();
}
long int wait4addrs[100];
void wait4__dmtcp_plt(){
  SETUP_FPTR(wait4);
  DELETE_CALL_FRAME();
}
long int waitidaddrs[100];
void waitid__dmtcp_plt(){
  SETUP_FPTR(waitid);
  DELETE_CALL_FRAME();
}
long int syscalladdrs[100];
void syscall__dmtcp_plt(){
  SETUP_FPTR(syscall);
  DELETE_CALL_FRAME();
}
long int popenaddrs[100];
void popen__dmtcp_plt(){
  SETUP_FPTR(popen);
  DELETE_CALL_FRAME();
}
long int pcloseaddrs[100];
void pclose__dmtcp_plt(){
  SETUP_FPTR(pclose);
  DELETE_CALL_FRAME();
}
long int openlogaddrs[100];
void openlog__dmtcp_plt(){
  SETUP_FPTR(openlog);
  DELETE_CALL_FRAME();
}
long int closelogaddrs[100];
void closelog__dmtcp_plt(){
  SETUP_FPTR(closelog);
  DELETE_CALL_FRAME();
}
//KJ long int __cloneaddrs[100];
//KJ void __clone__dmtcp_plt(){
//KJ   SETUP_FPTR(__clone);
//KJ   DELETE_CALL_FRAME();
//KJ }
long int pthread_createaddrs[100];
void pthread_create__dmtcp_plt(){
  SETUP_FPTR(pthread_create);
  DELETE_CALL_FRAME();
}
long int pthread_exitaddrs[100];
void pthread_exit__dmtcp_plt(){
  SETUP_FPTR(pthread_exit);
  DELETE_CALL_FRAME();
}
long int pthread_joinaddrs[100];
void pthread_join__dmtcp_plt(){
  SETUP_FPTR(pthread_join);
  DELETE_CALL_FRAME();
}
long int pthread_tryjoin_npaddrs[100];
void pthread_tryjoin_np__dmtcp_plt(){
  SETUP_FPTR(pthread_tryjoin_np);
  DELETE_CALL_FRAME();
}
long int pthread_timedjoin_npaddrs[100];
void pthread_timedjoin_np__dmtcp_plt(){
  SETUP_FPTR(pthread_timedjoin_np);
  DELETE_CALL_FRAME();
}
void * dmtcp_sdlsym(char *str, void *fptr, int pl_id, long int* addrs){
	char filename[200] = {0};
	strcat(filename, "./addrs/"); strcat(filename, str); strcat(filename, "__dmtcp.addr");
	if ((pl_id == 0 && addrs[0] == 0) || (pl_id > 0 && addrs[pl_id-1] == 0)){
    int numOfWrappers = 0;
    char *string = malloc(sizeof(char)*1000);
    int fd = open(filename, O_RDONLY);
    char *token;
    if (fd == -1) { printf("*** *** NO FILE\n"); exit(1); }
    read(fd, string, sizeof(char)*1000);
    while ((token = strsep(&string, ",")) != NULL)
      if (token[0] != '\0') {
        addrs[numOfWrappers++] = strtol(token, NULL, 16);
      }
    free(string);
    //initialized = 1;
  }
  while (1)
  {
    if (addrs[pl_id] != 0)
      return (void *)addrs[pl_id];
    ++pl_id;
  }
  exit(1);
  //return addrs[3];
  //return (void *) addrs[num];
  /*for (int i = 0; i < numOfWrappers; ++i) {
    if (caller < (void *) pthread_timedjoin_npaddrs[i])
      return (void *) pthread_timedjoin_npaddrs[i];
  }
  return (void *) pthread_timedjoin_npaddrs[0];*/
    }
