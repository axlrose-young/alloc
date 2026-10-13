# malloc-mini

A small memory allocator written in C. Desgined to be used in other C programs. Featuring alloc and unbound. 

## Build & Usage

```sh
git clone malloc-mini
cd malloc-mini
make all 
```

Usage:

```c
#include "alloc.h"
```
compile the program:

```sh
gcc main.c -L. -lalloc -o main
```

## About

Built due to the curiosity of malloc's working. Still a work in progress.
Planned to implement:
- Coalescing 
