
#ifndef VARIABLE_MEMORY_H
#define VARIABLE_MEMORY_H

#include "memory.h"
#include <mutex>

class VariableMemory : public Memory{

private:
struct Block{
    u_int64_t canary;
    size_t size;
    Block *next;
};

alignas(64)unsigned char pool_variable[MEMORY_POOL_SIZE];
Block *freeList = nullptr;
Block *first_pointer_boundary;
Block *last_pointer_boundary;

std::mutex mtx;

public:

    VariableMemory(void);
    void init_memory();
    void *allocate_memory(size_t);
    bool free_memory(void*);
    ~VariableMemory();

};
#endif