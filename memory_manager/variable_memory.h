
#ifndef VARIABLE_MEMORY_H
#define VARIABLE_MEMORY_H

#include "memory.h"
inline unsigned char pool_variable[MEMORY_POOL_SIZE];

class VariableMemory : public Memory{

private:
struct Block{
    size_t size;
    Block *next;
};

Block *freeList = nullptr;

public:

    VariableMemory(void);
    void init_memory();
    void *allocate_memory(size_t);
    void free_memory(void*);
    ~VariableMemory();

};
#endif