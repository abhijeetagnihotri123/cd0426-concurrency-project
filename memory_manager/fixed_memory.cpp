#include "fixed_memory.h"
#include <iostream>


void initMemory(){

    freeList = (Block*)pool;

    Block *current = freeList;
    std::cout<<current<<std::endl;

    size_t num_blocks = MEMORY_POOL_SIZE/sizeof(Block) - 1;

    for(int i = 0 ; i < num_blocks ; i++){

        current->next = (Block*)((unsigned char *)current + sizeof(Block));
        current = current->next;
    }
}

void *allocateFixedSizeMemory(){

    return nullptr;
}

void freeFixedSizeMemory(void *ptr){
    return;
}

int main(){

    initMemory();

    return 0;
}