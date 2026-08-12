#include <stdio.h>
#include <unistd.h>
#include <string.h>

#include "mem_alloc.h"

typedef struct {         
	size_t size;
	void* prevblock;
	void* nextblock;
	bool isallocated;
}Header;

size_t headersize = sizeof(Header); // size of metadata
void* prevblock = NULL;
void* nextblock = NULL;

void* mem_pull(size_t size){
	size += headersize; 	// includes metadata

	Header h = {0};
	h.size = size; 		// stores array size
	h.prevblock = prevblock;

	void* p = sbrk(size);
	h.isallocated = true;

	prevblock = p;
	nextblock = p;

	// store nextblock value in prev alloc
	if(h.prevblock != NULL){
		Header* tmp = (Header*)h.prevblock;
		tmp->nextblock = nextblock;
	}

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
	printf("curr block address  %p\n",tmp);	
	printf("prev block address  %p\n",h->prevblock);	
	printf("next block address  %p\n",h->nextblock);	
	puts("");
}

void mem_push(void* p){
	p -= headersize;		// points to curr start of block
	Header* curr = (Header*) p;
	
	curr->isallocated = false;	// deallocate block	

	/* Merge with prev if prev also deallocated
	   And update next block's prev addr */	

	if(curr->prevblock != NULL){ 
		Header* prev = (Header*)curr->prevblock;
		if(!prev->isallocated){
			prev->size += curr->size;	
			prev->nextblock = curr->nextblock;
			if(curr->nextblock != NULL){
				Header* next = (Header*)curr->nextblock;	
				next->prevblock = curr->prevblock;
			}
			// current now points to merged block
			curr = prev;
		}
	}
	if(curr->nextblock != NULL){
		Header* next = (Header*)curr->nextblock;
		if(!next->isallocated){
			curr->size += next->size;
			if(next->nextblock != NULL){
				curr->nextblock = next->nextblock;
			}
		}
	}	
}
