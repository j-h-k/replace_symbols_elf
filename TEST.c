#include <unistd.h>
#include <stdio.h>

void foo();
void doo();

int main()
{
	write(1,NULL,0);
	foo();
	//printf("foo is at: %p\n", foo);
	//printf("write is at: %p\n", write);
	

	return 0;
}


