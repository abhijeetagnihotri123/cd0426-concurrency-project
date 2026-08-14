#include "fixed_memory.h"

FixedMemory::FixedMemory(){
    init_memory();
}

void FixedMemory::init_memory(){

    freeList = (Block*)pool_fixed;

    Block *current = freeList;

    size_t num_blocks = MEMORY_POOL_SIZE/sizeof(Block) - 1;

    for(int i = 0 ; i < num_blocks ; i++){
        current->next = (Block*)((unsigned char *)current + sizeof(Block));
        current = current->next;
    }
    current->next = nullptr;

}

void* FixedMemory::allocate_memory(size_t size = 8){

    if(freeList == nullptr){
        std::cout<<"[Error : ]"<<"Memory pool exhausted or not allocated"<<std::endl;
        return nullptr;
    }

    Block *current = freeList;
    freeList = freeList->next;
    return (void *)current;
}

void FixedMemory::free_memory(void *ptr){
    
    if(ptr == nullptr){
        std::cout<<"[Error : ]"<<"Invalid memory pointer"<<std::endl;
        return;
    }
    Block *current = (Block*)ptr;
    current->next = freeList;
    freeList = current;
}

FixedMemory::~FixedMemory(){
    this->freeList = nullptr;
}

#if 0

int main(){

    Memory *m = new FixedMemory();
    m->init_memory();
    int *ptr = (int *)m->allocate_memory(1);

    if(ptr != nullptr){
        *ptr = 132;
        cout<<ptr<<" "<<*ptr<<endl;
        m->free_memory((void *)ptr);
    }

    return 0;
}
#endif