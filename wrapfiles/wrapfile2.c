#include <stdio.h>

void foo_wrap__dmtcp_3();

void foo_wrap() {
	printf("From wrapfile: 2\n");
	foo_wrap__dmtcp_3();
	printf("Return wrapfile: 2\n");
}
