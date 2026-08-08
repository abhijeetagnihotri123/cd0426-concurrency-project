#include "memory_pool.h"

struct Block{
    Block *next;
};

Block *freeList = nullptr;

void initMemory();

void *allocateFixedSizeMemory();

void freeFixedSizeMemory(void *);