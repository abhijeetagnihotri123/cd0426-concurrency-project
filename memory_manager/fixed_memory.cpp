#include "fixed_memory.h"
#include <iostream>


void initMemory(){

    freeList = (Block*)pool;

    Block *current = freeList;

    size_t num_blocks = MEMORY_POOL_SIZE/sizeof(Block) - 1;

    for(int i = 0 ; i < num_blocks ; i++){

        current->next = (Block*)((unsigned char *)current + sizeof(Block));
        current = current->next;
    }
}

void *allocateFixedSizeMemory(){

    if(freeList == nullptr){
        std::cout<<"[Error : ]"<<"Memory pool exhausted"<<std::endl;
        return nullptr;
    }

    Block *current = freeList;
    freeList = freeList->next;
    return (void *)current;
}

void freeFixedSizeMemory(void *ptr){
    
    if(ptr == nullptr){
        std::cout<<"[Error : ]"<<"Invalid memory pointer"<<std::endl;
        return;
    }

    Block *current = (Block*)ptr;
    current->next = freeList;
    freeList = current;

}

int main(){



    return 0;
}