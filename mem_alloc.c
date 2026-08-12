#include <stdio.h>
#include <unistd.h>
#include <string.h>

#include "mem_alloc.h"

typedef struct {         
	size_t size;
	bool isallocated;
}Header;

size_t headersize = sizeof(Header); // size of metadata


void* mem_pull(size_t size){
	size += headersize; 	// includes metadata

	Header h = {0};
	h.size = size; 		// stores array size
	h.isallocated = true; 

	void* p = sbrk(size);

	memcpy(p, &h, headersize);

	return p + headersize;
}

// Note: If arr pointer advanced then read metadata breaks 
// To do: explore writing the mem start address into metadata

// ONLY debug function
void read_metadata(const void* p){ 
	void* tmp = p;		
	tmp -= headersize;	
	Header* h = (Header*) tmp;
		
	printf("size of arr %ld\n",h->size);
	printf("arr alloc bool  %d\n",h->isallocated);	
}

void mem_push(void* p){
	p -= headersize;
	Header* h = (Header*) p;
	
	h->isallocated = false;

	// give the last deallocation back to os
}
