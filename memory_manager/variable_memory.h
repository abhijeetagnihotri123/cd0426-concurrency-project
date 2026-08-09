#include "memory_pool.h"

struct Block{
    size_t size;
    Block *next;
};

void init_variable_memory();

void *allocateVariableSizedMemory(size_t);

void freeVariableSizedMemory(void*);

