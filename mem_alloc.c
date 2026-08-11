#include <stdio.h>
#include <unistd.h>

void* my_alloc(size_t size){
	void* p = sbrk(size);
	return p;
}
