#include "variable_memory.h"

VariableMemory::VariableMemory(){
    init_memory();
}

void VariableMemory::init_memory(){
    freeList = (Block*)pool_variable;
    this->first_pointer_boundary = freeList;
    freeList->size = MEMORY_POOL_SIZE - sizeof(Block*);
    freeList->next = nullptr;
    freeList->canary = PREDEFINED_CANARY;
    this->last_pointer_boundary = (Block*)((unsigned char *)freeList +  freeList->size);
}

void *VariableMemory::allocate_memory(size_t size){

    std::lock_guard<std::mutex>lock(this->mtx);

    if(freeList == nullptr){
        std::cout<<"[Error : Memory pool exhausted]\n";
        return nullptr;
    }

    Block *current = freeList;
    Block *prev = nullptr;

    while(current != nullptr && current->size < size){
        prev = current;
        current = current->next;      
    }

    if(current == nullptr){
        return nullptr;
    }
    if(current->size > (sizeof(Block) + size)){
        Block *freeBlock = (Block*)((unsigned char *)current + sizeof(Block) + size);
        freeBlock->size = current->size - (sizeof(Block) + size);
        current->size = size; 
        freeBlock->next = current->next;
        current->next = freeBlock;
    }
    if(prev == nullptr){
        freeList = current->next;
    }
    else{
        prev->next = current->next;
    }
    current->canary = PREDEFINED_CANARY;
    return (void *)((unsigned char*)current + sizeof(Block));
}

bool VariableMemory::free_memory(void *ptr){
    
    std::lock_guard<std::mutex>lock(this->mtx);
    if(ptr == nullptr){
        std::cout<<"[Error : invalid pointer variable]\n";
        return false;
    }
    
    uintptr_t ptr_val = reinterpret_cast<uintptr_t>(ptr);
    uintptr_t base_val = reinterpret_cast<uintptr_t>(first_pointer_boundary);
    uintptr_t end_val = reinterpret_cast<uintptr_t>(last_pointer_boundary);

    bool is_aligned = ((ptr_val - base_val)%sizeof(Block) == 0);

    if(ptr_val < base_val || ptr_val > end_val || !is_aligned){
        std::cout<<"[Error : ] "<<"Invalid unaligned pointer value\n";
        return false;
    }

    Block *current = (Block*)((unsigned char *)ptr - sizeof(Block));

    if(current->canary != PREDEFINED_CANARY){
        std::cout<<"[Error : corrupted memory block]\n";
        return false;
    }

    current->next = freeList;
    freeList = current;
    while(current != nullptr && (current->next) != nullptr){
        if((unsigned char *)(current + sizeof(Block) + current->size) == (unsigned char *)current->next){
            current->size += current->next->size + sizeof(Block); 
            current->next = current->next->next;
        }
        else{
            current = current->next;
        }
    }
    return true;
}

VariableMemory::~VariableMemory(){
    init_memory();
}
