#ifndef FIXED_MEMORY_H
#define FIXED_MEMORY_H
#include "memory.h"
inline unsigned char pool_fixed[MEMORY_POOL_SIZE];

class FixedMemory : public Memory{

private:
    struct Block{
        Block *next;
    };  
    Block *freeList = nullptr;
public:
    FixedMemory(void);
    void init_memory(void);
    void *allocate_memory(size_t);
    void free_memory(void *);
    ~FixedMemory();
};


#endif