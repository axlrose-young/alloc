#include <stdio.h>
#include <unistd.h>
#include <string.h>

#include "mem_alloc.h"

typedef struct {         
	size_t size;
	void* prevblock;
	bool isallocated;
}Header;

size_t headersize = sizeof(Header); // size of metadata
void* prevblock = NULL;
void* curr_programbreak;

void* mem_pull(size_t size){
	size += headersize; 	// includes metadata

	Header h = {0};
	h.size = size; 		// stores array size
	h.prevblock = prevblock;

	void* p = sbrk(size);
	h.isallocated = true;
	prevblock = p;
	curr_programbreak = sbrk(0);

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
	printf("prev block address  %p\n",h->prevblock);	
	printf("curr block address  %p\n",tmp);	
	puts("");
}

void mem_push(void* p){
	p -= headersize;		// points to curr start of block
	Header* curr = (Header*) p;
	
	curr->isallocated = false;	// deallocate block

	// check for prev block
	if(curr->prevblock == NULL){
		return;
	}
	Header* prev = (Header*)curr->prevblock;
	if(!prev->isallocated){
		prev->size += curr->size; // add sizes
		if(curr_programbreak != (p + curr->size)){
			Header* next = (Header*) (p + curr->size);
			next->prevblock = prev->prevblock; 	// next to prev block addr
		}			
	}
}
