#include <stdio.h>
#include <unistd.h>
#include <string.h>

#include "mem_alloc.h"

void* mem_pull(size_t size){
	size += 8;
	void* p = sbrk(size);	

	header h;
	h.size = size;

	memcpy(p, &h, size);

	return p+8;
}

void read_metadata(void* p){
	p -= 8;
	header h;
	memcpy(&h, p, 8); 	
	printf("size of arr %ld\n",h.size);
}




