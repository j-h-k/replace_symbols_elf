#include <stdio.h>

#define times3(arg1, arg2) \
__asm__ ("leal (%0,%0,2),%0" :\
  "=r" (arg2) :\
  "0" (arg1) );

typedef void (*fptr)();

int hello(int x, int y)
{
  printf("Hello we are in hello(%d, %d)!\n", x, y);
  return x + y;
}

void * gethello()
{
  return (void *) &hello;
}

void * my_plt()
{
  fptr __fptr = (fptr) gethello();
  asm ("mov %%rbp, %%rax\n\t" 
       "sub %%rsp, %%rax\n\t"
       "add %%rax, %%rsp\n\t"
       "pop %%rbp\n\t"
       "jmp *%0"
       : 
       : "r" (__fptr)
       : "%rax");
  return NULL;
  //asm ("add $0x10, %%rsp\n\t" "pop %%rbp\n\t" "jmp *%0" : : "r" (__fptr));
}

int main()
{
/*  int x = 10, y = 777, z;
  printf("%d, %d\n", x, y);
  
  int arr[100] = {0};
  arr[10] = 111;

  times3(1, x);
  printf("%d, %d\n", x, y);

  asm ("leal (%1, %2, 4), %0" : "=r"(x) : "0" (5), "r"(10)); 
  printf("%d, %d\n", x, y);
*/
  int sum = my_plt(10, 20);
  printf("%d\n", sum);
  return 0;
}
