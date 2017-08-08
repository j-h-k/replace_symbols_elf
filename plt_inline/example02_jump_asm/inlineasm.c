#include <stdio.h>

#define times3(arg1, arg2) \
__asm__ ("leal (%0,%0,2),%0" :\
  "=r" (arg2) :\
  "0" (arg1) );

typedef void (*fptr)();

void hello()
{
  printf("Hello!\n");
}

void * gethello()
{
  return (void *) &hello;
}

int my_plt()
{
  fptr __fptr = (fptr) gethello();
  asm ("add $0x10, %%rsp\n\t" "pop %%rbp\n\t" "jmp *%0" : : "r" (__fptr));
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
  my_plt();
  return 0;
}
