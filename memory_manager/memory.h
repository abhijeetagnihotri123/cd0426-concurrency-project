#ifndef MEMORY_H
#define MEMORY_H

#include "memory_pool.h"
#include <stdint.h>

class Memory{

public:
    Memory(){}
    virtual void init_memory(void) = 0;
    virtual void *allocate_memory(size_t) = 0;
    virtual bool free_memory(void *) = 0;
    virtual ~Memory(){};
};

#endif