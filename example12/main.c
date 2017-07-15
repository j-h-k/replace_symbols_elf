#include <stdio.h>
#include <stdlib.h>


int main()
{
  char * ptr = malloc(sizeof(char));
  free(ptr);
  ptr = calloc(1, sizeof(char));
  free(ptr);
  printf("Program finished\n");
}
