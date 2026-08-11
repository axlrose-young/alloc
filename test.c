#include <stdio.h>
#include <string.h>

#include "mem_alloc.h"
#define SIZE 10

int main(){
	int* p = my_alloc(SIZE);

	// using the heap mem	
	memset(p, 0, SIZE);
}
