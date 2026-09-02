#include "FixedBlockAllocator_LockFree.hpp"

namespace Memory_Allocator_LockFree{



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
        return nullptr;
    }

    void FixedBlockAllocator_LockFree::my_free(void *ptr){

    }

    FixedBlockAllocator_LockFree::~FixedBlockAllocator_LockFree(void){

        front_.store(nullptr , std::memory_order_release);
        rear_.store(nullptr , std::memory_order_release);

    }

}