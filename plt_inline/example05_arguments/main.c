#include <stdio.h>
#include <stdarg.h>

void check_args(int count, ...)
{
  va_list ap;
  int i;

  va_start (ap, count);         /* Initialize the argument list. */

  for (i = 0; i < count; i++)
    printf("%d ", va_arg (ap, int));
  printf("\n");

  va_end (ap);                  /* Clean up. */
}

void * get_addr() { return &check_args; }

void not_on_stack()
{
  // NEED TO SAVE REGISTERS HERE LATER... (rdi, rsi, rdx, rcx, r8, r9, xmm0-7)
  extern void save_regs();
  extern void rest_regs();
  save_regs();
  get_addr(111, 222, 333, 444, 555, 666, 777, 888);
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
}

int main()
{
	not_on_stack(10, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10);
}
