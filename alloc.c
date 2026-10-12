#include <stdio.h>
#include <unistd.h>
#include <string.h>

#include "alloc.h"

static int reuse_check();

typedef struct {         
	size_t size;
	void* prevblock; 
	void* nextblock; 
	bool isallocated;
}Header;


size_t headersize = sizeof(Header); // size of metadata
void* prevblock = NULL;

void* mem_pull(size_t size){
	size += headersize; 	// includes metadata

	Header h = {0};
	h.size = size; 		// stores array size
	h.prevblock = prevblock;

	void* p = sbrk(size);
	h.isallocated = true;

	prevblock = p;
	void* nextblock = p;

	// store nextblock value in prev alloc
	if(h.prevblock != NULL){
		Header* tmp = (Header*)h.prevblock;
		tmp->nextblock = nextblock;
	}

	memcpy(p, &h, headersize);
	return p + headersize;
}

/*
 * Allocates a block with the metadata "sizeof(struct Node)" and the memory 
 * block needed
 *
 * A global struct tracks the allocs to get addresses
 *
 */

struct Node* head = NULL; /* points to first block */
struct Node* tail = NULL; /* tracks alloc */

void* 
alloc(size_t size) 
{
	if (reuse_check() == 0) { 	/* Check for block reusability */
	//	return reuse_block();
	}
	else {
		/* Normal alloc */
		struct Node* block = sbrk(sizeof(struct Node) + size);	

		if (block == (void*) -1) 
			return NULL;

		block->allocated = 1;
		block->size = size;

		if (tail == NULL) { 	/* first init */
			tail = block;	
			head = block;
		} else { 		/* filling prev block's next addr */
			tail->next = block;
			tail = block;
		}
		
		return (void*)(block + 1);
	}
}

static int 
reuse_check() {
	struct Node* x = head;	
	if (x == NULL) { 	/* Check if head is valid */
		return 1;
	}

	while(x->next != NULL) {
		if (!x->allocated) {
			printf("this block might be reusable");	
			return 0; 
		}	
		x = x->next;
	}	

	return 1;
}

void 
reuse_block() {
	
}

void
unbound(void* p) 
{
	struct Node* block = (struct Node*)p - 1;	

	if (!block->allocated) {
		fprintf(stderr, "Error: freeing unallocated mem\n");
		return;
	}

	block->allocated = 0;
}

// Note: If arr pointer advanced then read metadata breaks 
void 
read_metadata(void* p) 
{ 
	struct Node* rd = (struct Node*)p - 1;	
	
	printf("curr block addr %p\n",rd);
	printf("allocated: %d\n",rd->allocated);
	printf("size: %ld\n",rd->size);
	printf("Next block addr %p\n",rd->next);	
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
			curr->nextblock = next->nextblock;
		}
	}	

	/* change tail var "prevblock" position 
	   Done if the last block was coalesced */	
	Header* tail = (Header*) prevblock; 
	if(tail->isallocated){
		return;
	}
	// save the merged tail block 
	tail = curr;

	// walk prevblock back to last allocated
	Header* walk = (Header*) prevblock;	
	while(walk && !walk->isallocated){
		walk = (Header*) walk->prevblock;
	}
	prevblock = walk;
}
