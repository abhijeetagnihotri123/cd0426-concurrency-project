#include "variable_memory.h"

VariableMemory::VariableMemory(){
    init_memory();
}

void VariableMemory::init_memory(){
    freeList = (Block*)pool_variable;
    freeList->size = MEMORY_POOL_SIZE - sizeof(Block*);
    freeList->next = nullptr;
}

void *VariableMemory::allocate_memory(size_t size){

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
    return (void *)((unsigned char*)current + sizeof(Block));
}

bool VariableMemory::free_memory(void *ptr){
    if(ptr == nullptr){
        std::cout<<"[Error : invalid pointer variable]\n";
        return false;
    }
    Block *current = (Block*)((unsigned char *)ptr - sizeof(Block));
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
    this->freeList = nullptr;
}

#if 0

int main(){

    Memory *m = new VariableMemory();
    m->init_memory();
    int *ptr = (int *)m->allocate_memory(sizeof(int));

    if(ptr != nullptr){
        *ptr = 132;
        std::cout<<ptr<<" "<<*ptr<<std::endl;
        m->free_memory((void *)ptr);
    }

    return 0;
}
#endif