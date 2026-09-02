#include "FixedBlockAllocator_LockFree.hpp"

namespace Memory_Allocator_LockFree{

    FixedBlockAllocator_LockFree::FixedBlockAllocator_LockFree(void){
        init_memory();
    }

    void FixedBlockAllocator_LockFree::init_memory(void){

        Block *front,*rear;
        size_t block_size = sizeof(Block) + sizeof(adas::SensorFrame);
        size_t num_blocks = TOTAL_SIZE/block_size;

        front = rear = (Block*)pool;
        front->canary = rear->canary = CANARY_VALUE;

        for(size_t i = 0 ; i < num_blocks ; i++){

            Block *newPtr = (Block *)((unsigned char *)rear + block_size);
            newPtr->canary = CANARY_VALUE;
            rear->next = newPtr;
            rear = newPtr;
        }

        rear->next = nullptr;

        front_.store(front , std::memory_order_release);
        rear_.store(rear , std::memory_order_release);

    }

    void *FixedBlockAllocator_LockFree::my_malloc(void){
        Block *front = front_.load(std::memory_order_acquire);
        Block *rear = rear_.load(std::memory_order_acquire);

        if(front == nullptr){
            std::cout<<"[Error] : memory pool exhausted\n";
            return nullptr;
        }
        Block *block = front;

        if(front == rear){
            front = rear = nullptr;
        }
        else{
            front = front->next;
        }

        front_.store(front , std::memory_order_release);
        rear_.store(rear , std::memory_order_release);

        return (void *)((unsigned char *)block + sizeof(Block));
    }

    void FixedBlockAllocator_LockFree::my_free(void *ptr){

        if(ptr == nullptr){
            std::cout<<"[Error] : Null pointer cannot be accepted back\n";
            return;
        }

        Block *block = (Block*)((unsigned char *)ptr - sizeof(Block));
        if(block->canary != CANARY_VALUE){
            std::cout<<"[Error :] Corrupted memory reinitialising memory pool\n";
            init_memory();
            return;
        }

        block->next = nullptr;

        Block *front = front_.load(std::memory_order_acquire);
        Block *rear = rear_.load(std::memory_order_acquire);

        if(front == nullptr){
            front = rear = block;
        }
        else{
            rear->next = block;
            rear = block;
        }

        front_.store(front , std::memory_order_release);
        rear_.store(rear , std::memory_order_release);
    }

    FixedBlockAllocator_LockFree::~FixedBlockAllocator_LockFree(void){
        front_.store(nullptr , std::memory_order_release);
        rear_.store(nullptr , std::memory_order_release);
    }

}