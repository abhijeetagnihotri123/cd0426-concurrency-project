#ifndef FIXED_MEMORY_H
#define FIXED_MEMORY_H
#include "memory.h"
#include <stdint.h>
#define PREDEFINED_CANARY_VALUE 0xDEADBEEFDEADBEEF

class FixedMemory : public Memory{

private:
    alignas(64) unsigned char pool_fixed[MEMORY_POOL_SIZE];
    struct Block{
        Block *next;
        uint64_t canary;
    };  
    Block *freeList = nullptr;
    Block *last_pointer_boundary;
    Block *first_pointer_boundary;
public:
    FixedMemory(void);
    void init_memory(void);
    void *allocate_memory(size_t);
    bool free_memory(void *);
    ~FixedMemory();
};


#endif