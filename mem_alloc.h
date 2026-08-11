#ifndef MEM_ALLOC
#define MEM_ALLOC

typedef struct {
	size_t size;
}header;

void* mem_pull(size_t);
void read_metadata(void*);

#endif
