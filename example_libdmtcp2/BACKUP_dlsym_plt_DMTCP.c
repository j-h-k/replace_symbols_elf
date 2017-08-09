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
//extern void * dmtcp_sdlsym(char *, void *, char *, long int *);
//extern void * dmtcp_sdlsym(char *, void *, int, long int *);
long int signaladdrs[100];
//typedef sighandler_t func(int signum, sighandler_t handler);
sighandler_t signal__dmtcp_plt(int signum, sighandler_t handler){
  void * __fptr = (void *) NEXT_FNC_S_DEFAULT(signal);
asm ("mov %%rbp, %%rax\n\t" 
       "sub %%rsp, %%rax\n\t"
       "add %%rax, %%rsp\n\t"
       "pop %%rbp\n\t"
       "jmp *%0"
       : 
       : "r" (__fptr) 
       : "%rax");
}
long int sigactionaddrs[100];
//typedef int func(int signum, const struct sigaction *  act, struct sigaction *  oldact);
int sigaction__dmtcp_plt(int signum, const struct sigaction *  act, struct sigaction *  oldact){
  void * __fptr = (void *) NEXT_FNC_S_DEFAULT(sigaction);
asm ("mov %%rbp, %%rax\n\t" 
       "sub %%rsp, %%rax\n\t"
       "add %%rax, %%rsp\n\t"
       "pop %%rbp\n\t"
       "jmp *%0"
       : 
       : "r" (__fptr) 
       : "%rax");
}
long int rt_sigactionaddrs[100];
//typedef int func(int signum, const struct sigaction *  act, struct sigaction *  oldact);
//KJ int rt_sigaction__dmtcp_plt(int signum, const struct sigaction *  act, struct sigaction *  oldact){
//KJ   void * __fptr = (void *) NEXT_FNC_S_DEFAULT(rt_sigaction);
//KJ asm ("mov %%rbp, %%rax\n\t" 
//KJ        "sub %%rsp, %%rax\n\t"
//KJ        "add %%rax, %%rsp\n\t"
//KJ        "pop %%rbp\n\t"
//KJ        "jmp *%0"
//KJ        : 
//KJ        : "r" (__fptr) 
//KJ        : "%rax");
//KJ }
long int sigvecaddrs[100];
//typedef int func(int signum, const struct sigvec *  vec, struct sigvec *  ovec);
//KJ int sigvec__dmtcp_plt(int signum, const struct sigvec *  vec, struct sigvec *  ovec){
//KJ   void * __fptr = (void *) NEXT_FNC_S_DEFAULT(sigvec);
//KJ asm ("mov %%rbp, %%rax\n\t" 
//KJ        "sub %%rsp, %%rax\n\t"
//KJ        "add %%rax, %%rsp\n\t"
//KJ        "pop %%rbp\n\t"
//KJ        "jmp *%0"
//KJ        : 
//KJ        : "r" (__fptr) 
//KJ        : "%rax");
//KJ }
long int sigblockaddrs[100];
//typedef int func(int mask);
int sigblock__dmtcp_plt(int mask){
  void * __fptr = (void *) NEXT_FNC_S_DEFAULT(sigblock);
asm ("mov %%rbp, %%rax\n\t" 
       "sub %%rsp, %%rax\n\t"
       "add %%rax, %%rsp\n\t"
       "pop %%rbp\n\t"
       "jmp *%0"
       : 
       : "r" (__fptr) 
       : "%rax");
}
long int sigsetmaskaddrs[100];
//typedef int func(int mask);
int sigsetmask__dmtcp_plt(int mask){
  void * __fptr = (void *) NEXT_FNC_S_DEFAULT(sigsetmask);
asm ("mov %%rbp, %%rax\n\t" 
       "sub %%rsp, %%rax\n\t"
       "add %%rax, %%rsp\n\t"
       "pop %%rbp\n\t"
       "jmp *%0"
       : 
       : "r" (__fptr) 
       : "%rax");
}
long int siggetmaskaddrs[100];
//typedef int func(void);
int siggetmask__dmtcp_plt(void){
  void * __fptr = (void *) NEXT_FNC_S_DEFAULT(siggetmask);
asm ("mov %%rbp, %%rax\n\t" 
       "sub %%rsp, %%rax\n\t"
       "add %%rax, %%rsp\n\t"
       "pop %%rbp\n\t"
       "jmp *%0"
       : 
       : "r" (__fptr) 
       : "%rax");
}
long int sigprocmaskaddrs[100];
//typedef int func(int how, const sigset_t *  set, sigset_t *  oldset);
int sigprocmask__dmtcp_plt(int how, const sigset_t *  set, sigset_t *  oldset){
  void * __fptr = (void *) NEXT_FNC_S_DEFAULT(sigprocmask);
asm ("mov %%rbp, %%rax\n\t" 
       "sub %%rsp, %%rax\n\t"
       "add %%rax, %%rsp\n\t"
       "pop %%rbp\n\t"
       "jmp *%0"
       : 
       : "r" (__fptr) 
       : "%rax");
}
long int rt_sigprocmaskaddrs[100];
//typedef int func(int how, const sigset_t *  set, sigset_t *  oldset);
//KJ int rt_sigprocmask__dmtcp_plt(int how, const sigset_t *  set, sigset_t *  oldset){
//KJ   void * __fptr = (void *) NEXT_FNC_S_DEFAULT(rt_sigprocmask);
//KJ asm ("mov %%rbp, %%rax\n\t" 
//KJ        "sub %%rsp, %%rax\n\t"
//KJ        "add %%rax, %%rsp\n\t"
//KJ        "pop %%rbp\n\t"
//KJ        "jmp *%0"
//KJ        : 
//KJ        : "r" (__fptr) 
//KJ        : "%rax");
//KJ }
long int sigsuspendaddrs[100];
//typedef int func(const sigset_t *  mask);
int sigsuspend__dmtcp_plt(const sigset_t *  mask){
  void * __fptr = (void *) NEXT_FNC_S_DEFAULT(sigsuspend);
asm ("mov %%rbp, %%rax\n\t" 
       "sub %%rsp, %%rax\n\t"
       "add %%rax, %%rsp\n\t"
       "pop %%rbp\n\t"
       "jmp *%0"
       : 
       : "r" (__fptr) 
       : "%rax");
}
long int sigholdaddrs[100];
//typedef int func(int sig);
int sighold__dmtcp_plt(int sig){
  void * __fptr = (void *) NEXT_FNC_S_DEFAULT(sighold);
asm ("mov %%rbp, %%rax\n\t" 
       "sub %%rsp, %%rax\n\t"
       "add %%rax, %%rsp\n\t"
       "pop %%rbp\n\t"
       "jmp *%0"
       : 
       : "r" (__fptr) 
       : "%rax");
}
long int sigignoreaddrs[100];
//typedef int func(int sig);
int sigignore__dmtcp_plt(int sig){
  void * __fptr = (void *) NEXT_FNC_S_DEFAULT(sigignore);
asm ("mov %%rbp, %%rax\n\t" 
       "sub %%rsp, %%rax\n\t"
       "add %%rax, %%rsp\n\t"
       "pop %%rbp\n\t"
       "jmp *%0"
       : 
       : "r" (__fptr) 
       : "%rax");
}
long int sigrelseaddrs[100];
//typedef int func(int sig);
int sigrelse__dmtcp_plt(int sig){
  void * __fptr = (void *) NEXT_FNC_S_DEFAULT(sigrelse);
asm ("mov %%rbp, %%rax\n\t" 
       "sub %%rsp, %%rax\n\t"
       "add %%rax, %%rsp\n\t"
       "pop %%rbp\n\t"
       "jmp *%0"
       : 
       : "r" (__fptr) 
       : "%rax");
}
long int __sigpauseaddrs[100];
//typedef int func(int __sig_or_mask, int __is_sig);
//KJ int __sigpause__dmtcp_plt(int __sig_or_mask, int __is_sig){
//KJ   void * __fptr = (void *) NEXT_FNC_S_DEFAULT(__sigpause);
//KJ asm ("mov %%rbp, %%rax\n\t" 
//KJ        "sub %%rsp, %%rax\n\t"
//KJ        "add %%rax, %%rsp\n\t"
//KJ        "pop %%rbp\n\t"
//KJ        "jmp *%0"
//KJ        : 
//KJ        : "r" (__fptr) 
//KJ        : "%rax");
//KJ }
long int sigpauseaddrs[100];
//typedef int func(int sig);
int sigpause__dmtcp_plt(int sig){
  void * __fptr = (void *) NEXT_FNC_S_DEFAULT(sigpause);
asm ("mov %%rbp, %%rax\n\t" 
       "sub %%rsp, %%rax\n\t"
       "add %%rax, %%rsp\n\t"
       "pop %%rbp\n\t"
       "jmp *%0"
       : 
       : "r" (__fptr) 
       : "%rax");
}
long int pthread_sigmaskaddrs[100];
//typedef int func(int how, const sigset_t *  set, sigset_t *  oldmask);
int pthread_sigmask__dmtcp_plt(int how, const sigset_t *  set, sigset_t *  oldmask){
  void * __fptr = (void *) NEXT_FNC_S_DEFAULT(pthread_sigmask);
asm ("mov %%rbp, %%rax\n\t" 
       "sub %%rsp, %%rax\n\t"
       "add %%rax, %%rsp\n\t"
       "pop %%rbp\n\t"
       "jmp *%0"
       : 
       : "r" (__fptr) 
       : "%rax");
}
long int sigwaitaddrs[100];
//typedef int func(const sigset_t *  set, int *  sig);
int sigwait__dmtcp_plt(const sigset_t *  set, int *  sig){
  void * __fptr = (void *) NEXT_FNC_S_DEFAULT(sigwait);
asm ("mov %%rbp, %%rax\n\t" 
       "sub %%rsp, %%rax\n\t"
       "add %%rax, %%rsp\n\t"
       "pop %%rbp\n\t"
       "jmp *%0"
       : 
       : "r" (__fptr) 
       : "%rax");
}
long int sigwaitinfoaddrs[100];
//typedef int func(const sigset_t *  set, siginfo_t *  info);
int sigwaitinfo__dmtcp_plt(const sigset_t *  set, siginfo_t *  info){
  void * __fptr = (void *) NEXT_FNC_S_DEFAULT(sigwaitinfo);
asm ("mov %%rbp, %%rax\n\t" 
       "sub %%rsp, %%rax\n\t"
       "add %%rax, %%rsp\n\t"
       "pop %%rbp\n\t"
       "jmp *%0"
       : 
       : "r" (__fptr) 
       : "%rax");
}
long int sigtimedwaitaddrs[100];
//typedef int func(const sigset_t *  set, siginfo_t *  info, const struct timespec *  timeout);
int sigtimedwait__dmtcp_plt(const sigset_t *  set, siginfo_t *  info, const struct timespec *  timeout){
  void * __fptr = (void *) NEXT_FNC_S_DEFAULT(sigtimedwait);
asm ("mov %%rbp, %%rax\n\t" 
       "sub %%rsp, %%rax\n\t"
       "add %%rax, %%rsp\n\t"
       "pop %%rbp\n\t"
       "jmp *%0"
       : 
       : "r" (__fptr) 
       : "%rax");
}
long int forkaddrs[100];
//typedef pid_t func();
pid_t fork__dmtcp_plt(){
  void * __fptr = (void *) NEXT_FNC_S_DEFAULT(fork);
asm ("mov %%rbp, %%rax\n\t" 
       "sub %%rsp, %%rax\n\t"
       "add %%rax, %%rsp\n\t"
       "pop %%rbp\n\t"
       "jmp *%0"
       : 
       : "r" (__fptr) 
       : "%rax");
}
long int daemonaddrs[100];
//typedef int func(int nochdir, int noclose);
int daemon__dmtcp_plt(int nochdir, int noclose){
  void * __fptr = (void *) NEXT_FNC_S_DEFAULT(daemon);
asm ("mov %%rbp, %%rax\n\t" 
       "sub %%rsp, %%rax\n\t"
       "add %%rax, %%rsp\n\t"
       "pop %%rbp\n\t"
       "jmp *%0"
       : 
       : "r" (__fptr) 
       : "%rax");
}
long int vforkaddrs[100];
//typedef pid_t func();
pid_t vfork__dmtcp_plt(){
  void * __fptr = (void *) NEXT_FNC_S_DEFAULT(vfork);
asm ("mov %%rbp, %%rax\n\t" 
       "sub %%rsp, %%rax\n\t"
       "add %%rax, %%rsp\n\t"
       "pop %%rbp\n\t"
       "jmp *%0"
       : 
       : "r" (__fptr) 
       : "%rax");
}
long int execveaddrs[100];
//typedef int func(const char * filename, char * const argv[], char * const envp[]);
int execve__dmtcp_plt(const char * filename, char * const argv[], char * const envp[]){
  void * __fptr = (void *) NEXT_FNC_S_DEFAULT(execve);
asm ("mov %%rbp, %%rax\n\t" 
       "sub %%rsp, %%rax\n\t"
       "add %%rax, %%rsp\n\t"
       "pop %%rbp\n\t"
       "jmp *%0"
       : 
       : "r" (__fptr) 
       : "%rax");
}
long int execvaddrs[100];
//typedef int func(const char * path, char * const argv[]);
int execv__dmtcp_plt(const char * path, char * const argv[]){
  void * __fptr = (void *) NEXT_FNC_S_DEFAULT(execv);
asm ("mov %%rbp, %%rax\n\t" 
       "sub %%rsp, %%rax\n\t"
       "add %%rax, %%rsp\n\t"
       "pop %%rbp\n\t"
       "jmp *%0"
       : 
       : "r" (__fptr) 
       : "%rax");
}
long int execvpaddrs[100];
//typedef int func(const char * filename, char * const argv[]);
int execvp__dmtcp_plt(const char * filename, char * const argv[]){
  void * __fptr = (void *) NEXT_FNC_S_DEFAULT(execvp);
asm ("mov %%rbp, %%rax\n\t" 
       "sub %%rsp, %%rax\n\t"
       "add %%rax, %%rsp\n\t"
       "pop %%rbp\n\t"
       "jmp *%0"
       : 
       : "r" (__fptr) 
       : "%rax");
}
long int execvpeaddrs[100];
//typedef int func(const char * filename, char * const argv[], char * const envp[]);
int execvpe__dmtcp_plt(const char * filename, char * const argv[], char * const envp[]){
  void * __fptr = (void *) NEXT_FNC_S_DEFAULT(execvpe);
asm ("mov %%rbp, %%rax\n\t" 
       "sub %%rsp, %%rax\n\t"
       "add %%rax, %%rsp\n\t"
       "pop %%rbp\n\t"
       "jmp *%0"
       : 
       : "r" (__fptr) 
       : "%rax");
}
long int fexecveaddrs[100];
//typedef int func(int fd, char * const argv[], char * const envp[]);
int fexecve__dmtcp_plt(int fd, char * const argv[], char * const envp[]){
  void * __fptr = (void *) NEXT_FNC_S_DEFAULT(fexecve);
asm ("mov %%rbp, %%rax\n\t" 
       "sub %%rsp, %%rax\n\t"
       "add %%rax, %%rsp\n\t"
       "pop %%rbp\n\t"
       "jmp *%0"
       : 
       : "r" (__fptr) 
       : "%rax");
}
long int execladdrs[100];
//typedef int func(const char * path, const char * arg, ...);
int execl__dmtcp_plt(const char * path, const char * arg, ...){
  void * __fptr = (void *) NEXT_FNC_S_DEFAULT(execl);
asm ("mov %%rbp, %%rax\n\t" 
       "sub %%rsp, %%rax\n\t"
       "add %%rax, %%rsp\n\t"
       "pop %%rbp\n\t"
       "jmp *%0"
       : 
       : "r" (__fptr) 
       : "%rax");
}
long int execlpaddrs[100];
//typedef int func(const char * file, const char * arg, ...);
int execlp__dmtcp_plt(const char * file, const char * arg, ...){
  void * __fptr = (void *) NEXT_FNC_S_DEFAULT(execlp);
asm ("mov %%rbp, %%rax\n\t" 
       "sub %%rsp, %%rax\n\t"
       "add %%rax, %%rsp\n\t"
       "pop %%rbp\n\t"
       "jmp *%0"
       : 
       : "r" (__fptr) 
       : "%rax");
}
long int execleaddrs[100];
//typedef int func(const char * path, const char * arg, ...);
int execle__dmtcp_plt(const char * path, const char * arg, ...){
  void * __fptr = (void *) NEXT_FNC_S_DEFAULT(execle);
asm ("mov %%rbp, %%rax\n\t" 
       "sub %%rsp, %%rax\n\t"
       "add %%rax, %%rsp\n\t"
       "pop %%rbp\n\t"
       "jmp *%0"
       : 
       : "r" (__fptr) 
       : "%rax");
}
long int systemaddrs[100];
//typedef int func(const char * line);
int system__dmtcp_plt(const char * line){
  void * __fptr = (void *) NEXT_FNC_S_DEFAULT(system);
asm ("mov %%rbp, %%rax\n\t" 
       "sub %%rsp, %%rax\n\t"
       "add %%rax, %%rsp\n\t"
       "pop %%rbp\n\t"
       "jmp *%0"
       : 
       : "r" (__fptr) 
       : "%rax");
}
long int exitaddrs[100];
//typedef void func(int status);
void exit__dmtcp_plt(int status){
  void * __fptr = (void *) NEXT_FNC_S_DEFAULT(exit);
asm ("mov %%rbp, %%rax\n\t" 
       "sub %%rsp, %%rax\n\t"
       "add %%rax, %%rsp\n\t"
       "pop %%rbp\n\t"
       "jmp *%0"
       : 
       : "r" (__fptr) 
       : "%rax");
}
long int closeaddrs[100];
//typedef int func(int fd);
int close__dmtcp_plt(int fd){
  void * __fptr = (void *) NEXT_FNC_S_DEFAULT(close);
asm ("mov %%rbp, %%rax\n\t" 
       "sub %%rsp, %%rax\n\t"
       "add %%rax, %%rsp\n\t"
       "pop %%rbp\n\t"
       "jmp *%0"
       : 
       : "r" (__fptr) 
       : "%rax");
}
long int fcloseaddrs[100];
//typedef int func(FILE * fp);
int fclose__dmtcp_plt(FILE * fp){
  void * __fptr = (void *) NEXT_FNC_S_DEFAULT(fclose);
asm ("mov %%rbp, %%rax\n\t" 
       "sub %%rsp, %%rax\n\t"
       "add %%rax, %%rsp\n\t"
       "pop %%rbp\n\t"
       "jmp *%0"
       : 
       : "r" (__fptr) 
       : "%rax");
}
long int closediraddrs[100];
//typedef int func(DIR * dir);
int closedir__dmtcp_plt(DIR * dir){
  void * __fptr = (void *) NEXT_FNC_S_DEFAULT(closedir);
asm ("mov %%rbp, %%rax\n\t" 
       "sub %%rsp, %%rax\n\t"
       "add %%rax, %%rsp\n\t"
       "pop %%rbp\n\t"
       "jmp *%0"
       : 
       : "r" (__fptr) 
       : "%rax");
}
long int dup2addrs[100];
//typedef int func(int oldfd, int newfd);
int dup2__dmtcp_plt(int oldfd, int newfd){
  void * __fptr = (void *) NEXT_FNC_S_DEFAULT(dup2);
asm ("mov %%rbp, %%rax\n\t" 
       "sub %%rsp, %%rax\n\t"
       "add %%rax, %%rsp\n\t"
       "pop %%rbp\n\t"
       "jmp *%0"
       : 
       : "r" (__fptr) 
       : "%rax");
}
long int pipeaddrs[100];
//typedef int func(int fds[2]);
int pipe__dmtcp_plt(int fds[2]){
  void * __fptr = (void *) NEXT_FNC_S_DEFAULT(pipe);
asm ("mov %%rbp, %%rax\n\t" 
       "sub %%rsp, %%rax\n\t"
       "add %%rax, %%rsp\n\t"
       "pop %%rbp\n\t"
       "jmp *%0"
       : 
       : "r" (__fptr) 
       : "%rax");
}
long int pipe2addrs[100];
//typedef int func(int fds[2], int flags);
int pipe2__dmtcp_plt(int fds[2], int flags){
  void * __fptr = (void *) NEXT_FNC_S_DEFAULT(pipe2);
asm ("mov %%rbp, %%rax\n\t" 
       "sub %%rsp, %%rax\n\t"
       "add %%rax, %%rsp\n\t"
       "pop %%rbp\n\t"
       "jmp *%0"
       : 
       : "r" (__fptr) 
       : "%rax");
}
long int waitaddrs[100];
//typedef pid_t func(__WAIT_STATUS stat_loc);
pid_t wait__dmtcp_plt(__WAIT_STATUS stat_loc){
  void * __fptr = (void *) NEXT_FNC_S_DEFAULT(wait);
asm ("mov %%rbp, %%rax\n\t" 
       "sub %%rsp, %%rax\n\t"
       "add %%rax, %%rsp\n\t"
       "pop %%rbp\n\t"
       "jmp *%0"
       : 
       : "r" (__fptr) 
       : "%rax");
}
long int waitpidaddrs[100];
//typedef pid_t func(pid_t pid, int * stat_loc, int options);
pid_t waitpid__dmtcp_plt(pid_t pid, int * stat_loc, int options){
  void * __fptr = (void *) NEXT_FNC_S_DEFAULT(waitpid);
asm ("mov %%rbp, %%rax\n\t" 
       "sub %%rsp, %%rax\n\t"
       "add %%rax, %%rsp\n\t"
       "pop %%rbp\n\t"
       "jmp *%0"
       : 
       : "r" (__fptr) 
       : "%rax");
}
long int wait3addrs[100];
//typedef pid_t func(__WAIT_STATUS status, int options, struct rusage * rusage);
pid_t wait3__dmtcp_plt(__WAIT_STATUS status, int options, struct rusage * rusage){
  void * __fptr = (void *) NEXT_FNC_S_DEFAULT(wait3);
asm ("mov %%rbp, %%rax\n\t" 
       "sub %%rsp, %%rax\n\t"
       "add %%rax, %%rsp\n\t"
       "pop %%rbp\n\t"
       "jmp *%0"
       : 
       : "r" (__fptr) 
       : "%rax");
}
long int wait4addrs[100];
//typedef pid_t func(pid_t pid, __WAIT_STATUS status, int options, struct rusage * rusage);
pid_t wait4__dmtcp_plt(pid_t pid, __WAIT_STATUS status, int options, struct rusage * rusage){
  void * __fptr = (void *) NEXT_FNC_S_DEFAULT(wait4);
asm ("mov %%rbp, %%rax\n\t" 
       "sub %%rsp, %%rax\n\t"
       "add %%rax, %%rsp\n\t"
       "pop %%rbp\n\t"
       "jmp *%0"
       : 
       : "r" (__fptr) 
       : "%rax");
}
long int waitidaddrs[100];
//typedef int func(idtype_t idtype, id_t id, siginfo_t * infop, int options);
int waitid__dmtcp_plt(idtype_t idtype, id_t id, siginfo_t * infop, int options){
  void * __fptr = (void *) NEXT_FNC_S_DEFAULT(waitid);
asm ("mov %%rbp, %%rax\n\t" 
       "sub %%rsp, %%rax\n\t"
       "add %%rax, %%rsp\n\t"
       "pop %%rbp\n\t"
       "jmp *%0"
       : 
       : "r" (__fptr) 
       : "%rax");
}
long int syscalladdrs[100];
//typedef long func(long sys_num, ...);
long syscall__dmtcp_plt(long sys_num, ...){
  void * __fptr = (void *) NEXT_FNC_S_DEFAULT(syscall);
asm ("mov %%rbp, %%rax\n\t" 
       "sub %%rsp, %%rax\n\t"
       "add %%rax, %%rsp\n\t"
       "pop %%rbp\n\t"
       "jmp *%0"
       : 
       : "r" (__fptr) 
       : "%rax");
}
long int popenaddrs[100];
//typedef FILE * func(const char * command, const char * mode);
FILE * popen__dmtcp_plt(const char * command, const char * mode){
  void * __fptr = (void *) NEXT_FNC_S_DEFAULT(popen);
asm ("mov %%rbp, %%rax\n\t" 
       "sub %%rsp, %%rax\n\t"
       "add %%rax, %%rsp\n\t"
       "pop %%rbp\n\t"
       "jmp *%0"
       : 
       : "r" (__fptr) 
       : "%rax");
}
long int pcloseaddrs[100];
//typedef int func(FILE * fp);
int pclose__dmtcp_plt(FILE * fp){
  void * __fptr = (void *) NEXT_FNC_S_DEFAULT(pclose);
asm ("mov %%rbp, %%rax\n\t" 
       "sub %%rsp, %%rax\n\t"
       "add %%rax, %%rsp\n\t"
       "pop %%rbp\n\t"
       "jmp *%0"
       : 
       : "r" (__fptr) 
       : "%rax");
}
long int openlogaddrs[100];
//typedef void func(const char * ident, int option, int facility);
void openlog__dmtcp_plt(const char * ident, int option, int facility){
  void * __fptr = (void *) NEXT_FNC_S_DEFAULT(openlog);
asm ("mov %%rbp, %%rax\n\t" 
       "sub %%rsp, %%rax\n\t"
       "add %%rax, %%rsp\n\t"
       "pop %%rbp\n\t"
       "jmp *%0"
       : 
       : "r" (__fptr) 
       : "%rax");
}
long int closelogaddrs[100];
//typedef void func(void);
void closelog__dmtcp_plt(void){
  void * __fptr = (void *) NEXT_FNC_S_DEFAULT(closelog);
asm ("mov %%rbp, %%rax\n\t" 
       "sub %%rsp, %%rax\n\t"
       "add %%rax, %%rsp\n\t"
       "pop %%rbp\n\t"
       "jmp *%0"
       : 
       : "r" (__fptr) 
       : "%rax");
}
long int __cloneaddrs[100];
//typedef int func(int (* fn)(void * arg), void * child_stack, int flags, void * arg, int * parent_tidptr, struct user_desc * newtls, int * child_tidptr);
//KJ int __clone__dmtcp_plt(int (* fn)(void * arg), void * child_stack, int flags, void * arg, int * parent_tidptr, struct user_desc * newtls, int * child_tidptr){
//KJ   void * __fptr = (void *) NEXT_FNC_S_DEFAULT(__clone);
//KJ asm ("mov %%rbp, %%rax\n\t" 
//KJ        "sub %%rsp, %%rax\n\t"
//KJ        "add %%rax, %%rsp\n\t"
//KJ        "pop %%rbp\n\t"
//KJ        "jmp *%0"
//KJ        : 
//KJ        : "r" (__fptr) 
//KJ        : "%rax");
//KJ }
long int pthread_createaddrs[100];
//typedef int func(pthread_t * thread, const pthread_attr_t * attr, void * (* start_routine)(void *), void * arg);
int pthread_create__dmtcp_plt(pthread_t * thread, const pthread_attr_t * attr, void * (* start_routine)(void *), void * arg){
  void * __fptr = (void *) NEXT_FNC_S_DEFAULT(pthread_create);
asm ("mov %%rbp, %%rax\n\t" 
       "sub %%rsp, %%rax\n\t"
       "add %%rax, %%rsp\n\t"
       "pop %%rbp\n\t"
       "jmp *%0"
       : 
       : "r" (__fptr) 
       : "%rax");
}
long int pthread_exitaddrs[100];
//typedef void func(void * retval);
void pthread_exit__dmtcp_plt(void * retval){
  void * __fptr = (void *) NEXT_FNC_S_DEFAULT(pthread_exit);
asm ("mov %%rbp, %%rax\n\t" 
       "sub %%rsp, %%rax\n\t"
       "add %%rax, %%rsp\n\t"
       "pop %%rbp\n\t"
       "jmp *%0"
       : 
       : "r" (__fptr) 
       : "%rax");
}
long int pthread_joinaddrs[100];
//typedef int func(pthread_t thread, void * * retval);
int pthread_join__dmtcp_plt(pthread_t thread, void * * retval){
  void * __fptr = (void *) NEXT_FNC_S_DEFAULT(pthread_join);
asm ("mov %%rbp, %%rax\n\t" 
       "sub %%rsp, %%rax\n\t"
       "add %%rax, %%rsp\n\t"
       "pop %%rbp\n\t"
       "jmp *%0"
       : 
       : "r" (__fptr) 
       : "%rax");
}
long int pthread_tryjoin_npaddrs[100];
//typedef int func(pthread_t thread, void * * retval);
int pthread_tryjoin_np__dmtcp_plt(pthread_t thread, void * * retval){
  void * __fptr = (void *) NEXT_FNC_S_DEFAULT(pthread_tryjoin_np);
asm ("mov %%rbp, %%rax\n\t" 
       "sub %%rsp, %%rax\n\t"
       "add %%rax, %%rsp\n\t"
       "pop %%rbp\n\t"
       "jmp *%0"
       : 
       : "r" (__fptr) 
       : "%rax");
}
long int pthread_timedjoin_npaddrs[100];
//typedef int func(pthread_t thread, void * * retval, const struct timespec * abstime);
int pthread_timedjoin_np__dmtcp_plt(pthread_t thread, void * * retval, const struct timespec * abstime){
  void * __fptr = (void *) NEXT_FNC_S_DEFAULT(pthread_timedjoin_np);
asm ("mov %%rbp, %%rax\n\t" 
       "sub %%rsp, %%rax\n\t"
       "add %%rax, %%rsp\n\t"
       "pop %%rbp\n\t"
       "jmp *%0"
       : 
       : "r" (__fptr) 
       : "%rax");
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
  //return addrs[3];
  //return (void *) addrs[num];
  /*for (int i = 0; i < numOfWrappers; ++i) {
    if (caller < (void *) pthread_timedjoin_npaddrs[i])
      return (void *) pthread_timedjoin_npaddrs[i];
  }
  return (void *) pthread_timedjoin_npaddrs[0];*/
    }
