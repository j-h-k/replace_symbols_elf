#include <stdio.h>

void foo_wrap__dmtcp_2();

void foo_wrap() {
	printf("From wrapfile: 1\n");
	foo_wrap__dmtcp_2();
}
