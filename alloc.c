#include <stdio.h>
#include <unistd.h>
#include <string.h>

#include "alloc.h"

static struct Node* reuse_check(size_t);
static void* reuse_block(struct Node* reuse, size_t size);

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
	struct Node* reuse = reuse_check(size);
	if (reuse != NULL)  		/* Check for block reusability */
		return reuse_block(reuse, size);
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

static struct Node*
reuse_check(size_t size) 
{
	struct Node* x = head;	
	if (x == NULL) { 	/* Check if head is valid */
		return NULL;
	}

	while(x != NULL) {
		if ((!x->allocated) && (x->size > size)) 	
			return x;
		x = x->next;
	}	

	return NULL;
}

static void*
reuse_block(struct Node* reuse, size_t size) 
{
	reuse->size = size;		
	reuse->allocated = 1;

	return (void*)(reuse + 1);
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

/* Note: If arr pointer advanced then read metadata breaks */
void 
read_metadata(void* p) 
{ 
	struct Node* rd = (struct Node*)p - 1;	
	
	printf("curr block addr %p\n",rd);
	printf("allocated: %d\n",rd->allocated);
	printf("size: %ld\n",rd->size);
	printf("Next block addr %p\n",rd->next);	
}
