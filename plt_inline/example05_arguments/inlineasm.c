#include <stdarg.h>
#include <stdio.h>
#include <stdint.h>

// Mimic wrapper function
int aeu(int count,...)
{
  va_list ap;
  int i, sum;

  va_start (ap, count);         /* Initialize the argument list. */

  sum = 0;
  for (i = 0; i < count; i++)
    sum += va_arg (ap, int);    /* Get the next argument value. */

  va_end (ap);                  /* Clean up. */
  return sum;
}

// Mimic dmtcp_sdlysm
void * get_aeu(int dummy)
{
  return (void *) &aeu;
}

// Mimic <symbol>__dmtcp_plt
void * plt_aeu()
{
  asm("sub $0x70, %%rsp\n\t"
      : 
      : 
      :); 
  /* RDI, RSI, RDX, RCX, R8, R9, XMM0–7 */
  get_aeu(1); 
  asm ("mov %%rax, %%r10\n\t" 
       "mov %%rbp, %%r11\n\t" 
       "sub %%rsp, %%r11\n\t"
       "add %%r11, %%rsp\n\t"
       "pop %%rbp\n\t"
       "jmp *%%r10"
       : 
       :
       : );
  return NULL;
}

int main()
{
  /* Registers used: %edi %esi %edx  */
  printf("Plt : Sum 10 + 20 = %ld (should be 30)\n", (int64_t)(plt_aeu(2, 10, 20)));

  /* Registers used: %edi %esi %edx %ecx %r8d %r9d (rest pushed onto stack)  */
  printf("Plt : Sum 1 to 10 = %ld (should be 55)\n", (int64_t)(plt_aeu(10, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10)));
  return 0;
}
