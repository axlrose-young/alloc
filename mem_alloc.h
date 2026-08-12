#ifndef MEM_ALLOC
#define MEM_ALLOC

void* mem_pull(size_t);
void mem_push(void*);
void read_metadata(const void*);
#endif
