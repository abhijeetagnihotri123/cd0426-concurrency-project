#include "variable_memory.h"

Block *freeList = nullptr;

void init_variable_memory(){
    freeList = (Block*)pool;
    freeList->size = MEMORY_POOL_SIZE - sizeof(Block*);
    freeList->next = nullptr;
}

void *allocateVariableSizedMemory(size_t size){

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
    return current;
}

void freeVariableSizedMemory(void *ptr){
    if(ptr == nullptr){
        std::cout<<"[Error : invalid pointer variable]\n";
    }
    Block *current = (Block*)ptr;
    current->next = freeList;
    freeList = current;
}

struct Data{
    int x,y;
};

int main(){

    init_variable_memory();

    int *ptr = (int *)allocateVariableSizedMemory(sizeof(int));
    
    if(ptr != nullptr){
        *ptr = 35;
        std::cout<<"Allocator is working : "<<ptr<<" -> "<<*ptr<<std::endl;
        freeVariableSizedMemory((void *)ptr);
    }

    Data *d = (Data *)allocateVariableSizedMemory(sizeof(Data));

    if(d != nullptr){
        d->x = 132;
        d->y = 264;
        std::cout<<"Allocator for Data struct : ["<<d<<","<<d->x<<","<<d->y<<"]\n";
        freeVariableSizedMemory((void *)d);
    }

    

    return 0;
}