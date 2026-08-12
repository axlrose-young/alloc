#include <stdio.h>
#include <unistd.h>
#include <string.h>

#include "mem_alloc.h"

typedef struct {         
	size_t size;
	bool isallocated;
}header;

size_t headersize = sizeof(header);

void* mem_pull(size_t size){
	header h = {0};
	h.size = size;
	h.isallocated = true;

	printf("size of struct: %ld\n",headersize);

	size += headersize;
	void* p = sbrk(size);

	memcpy(p, &h, headersize);

	return p + headersize;
}

void read_metadata(void* p){
	p -= headersize;
	header h;
	memcpy(&h, p, headersize); 	
	printf("size of arr %ld\n",h.size);
}
