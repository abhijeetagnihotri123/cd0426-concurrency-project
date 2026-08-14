
#include "memory_pool.h"

#ifndef MEMORY_H
#define MEMORY_H


class Memory{

public:
    Memory(){}
    virtual void init_memory(void) = 0;
    virtual void *allocate_memory(size_t) = 0;
    virtual void free_memory(void *) = 0;
    virtual ~Memory(){};
};

#endif