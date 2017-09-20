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
void * get_aeu(int dummy1, int dummy2, int dummy3, int dummy4, int dummy5, int dummy6, int dummy7, int dummy8)
{
  return (void *) &aeu;
}

// Mimic <symbol>__dmtcp_plt
void * plt_aeu()
{
  extern void save_regs();
  extern void rest_regs();
  save_regs();
  /* RDI, RSI, RDX, RCX, R8, R9, XMM0–7 */
  get_aeu(1, 2, 3, 4, 5, 6, 7, 8); 
  asm volatile ("mov %%rax, %%r10\n\t" : : : );
  rest_regs();
  asm (//"mov %%rax, %%r10\n\t"
       //"mov %%rbp, %%r11\n\t"
       //"sub %%rsp, %%r11\n\t"
       //"add %%r11, %%rsp\n\t"
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
  printf("Plt : Sum 101, 202, ... 808 = %ld (should be 3636)\n", (int64_t)(plt_aeu(8, 101, 202, 303, 404, 505, 606, 707, 808)));

  /* Registers used: %edi %esi %edx %ecx %r8d %r9d (rest pushed onto stack)  */
  printf("Plt : Sum 1 to 10 = %ld (should be 55)\n", (int64_t)(plt_aeu(10, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10)));
  return 0;
}
