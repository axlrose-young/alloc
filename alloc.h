#ifndef MEM_ALLOC
#define MEM_ALLOC

struct Node {
	bool allocated;
	size_t size;
	struct Node* next;
};

void* alloc(size_t);
void unbound(void*);

void* mem_pull(size_t);
void mem_push(void*);
void read_metadata(void*);

#endif
