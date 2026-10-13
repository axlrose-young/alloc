#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "alloc.h"
#define SIZE 10

int main(){

	void* ptr = alloc(100);
	unbound(ptr);

	printf("This ran\n");

	return 0;
}
