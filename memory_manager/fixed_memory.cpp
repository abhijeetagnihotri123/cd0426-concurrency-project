#include "fixed_memory.h"

FixedMemory::FixedMemory(){
    init_memory();
}

void FixedMemory::init_memory(){

    freeList = (Block*)pool_fixed;

    Block *current = freeList;

    size_t num_blocks = MEMORY_POOL_SIZE/sizeof(Block) - 1;

    this->first_pointer_boundary = freeList;

    for(int i = 0 ; i < num_blocks ; i++){
        current->canary = PREDEFINED_CANARY_VALUE;
        current->next = (Block*)((unsigned char *)current + sizeof(Block));
        current = current->next;
    }
    current->next = nullptr;

    current = freeList;

    this->last_pointer_boundary = current;
}

void* FixedMemory::allocate_memory(size_t size = 8){

    if(freeList == nullptr || size > sizeof(Block)){
        std::cout<<"[Error : ] "<<"Memory pool exhausted or requested size exceeds allowed allocation size"<<std::endl;
        return nullptr;
    }

    Block *current = freeList;
    freeList = freeList->next;
    return (void *)current;
}

bool FixedMemory::free_memory(void *ptr){
    
    if(ptr == nullptr){
        std::cout<<"[Error : ] "<<"Invalid memory pointer"<<std::endl;
        return false;
    }

    uintptr_t ptr_val = reinterpret_cast<uintptr_t>(ptr);
    uintptr_t base_val = reinterpret_cast<uintptr_t>(first_pointer_boundary);
    uintptr_t end_val = reinterpret_cast<uintptr_t>(last_pointer_boundary);

    bool is_aligned = ((ptr_val - base_val) % sizeof(Block) == 0);

    if(ptr_val < base_val || ptr_val > end_val || !is_aligned){
        std::cout<<"[Error : ] "<<"Invalid memory pointer, either out of bounds or misaligned"<<std::endl;
        return false;
    }

    Block *current = (Block*)ptr;
    
    if(current->canary != PREDEFINED_CANARY_VALUE){
        std::cout<<"[Error : ] "<<"Corrupted memory as canaries don't match reseting memory"<<std::endl;
        init_memory();
        return false;
    }

    current->next = freeList;
    freeList = current;
    return true;
}

FixedMemory::~FixedMemory(){
    this->freeList = nullptr;
}
