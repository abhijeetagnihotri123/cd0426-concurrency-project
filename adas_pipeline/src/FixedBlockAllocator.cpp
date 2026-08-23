#include "FixedBlockAllocator.hpp"

namespace Memory_Allocator{

    FixedBlockAllocator::FixedBlockAllocator(void){
        init_memory();
    }

    void FixedBlockAllocator::init_memory(void){
        this->front = this->rear = (Block*)pool;
        size_t block_size = sizeof(Block) + sizeof(adas::SensorFrame);
        size_t num_blocks = TOTAL_SIZE/block_size;

        this->front->canary = this->rear->canary = CANARY_VALUE;
        for(size_t i = 0 ; i < num_blocks ; i++){

            Block *newPtr = (Block *)((unsigned char *)this->rear + block_size);
            newPtr->canary = CANARY_VALUE;
            rear->next = newPtr;
            rear = newPtr;
        }
        this->rear->next = nullptr;
    }

    void *FixedBlockAllocator::my_malloc(void){

        std::lock_guard<std::mutex>lock(allocator_mutex);
        if(this->front == nullptr){
            std::cout<<"[Error :] Memory pool exhausted\n";
            return nullptr;
        }
        Block *block = this->front;
        if(this->front == this->rear){
            this->front = this->rear = nullptr;
        }
        else{
            this->front = this->front->next;
        }
        void *ptr = (void *)((unsigned char *)block + sizeof(Block));
        return ptr;
    }

    void FixedBlockAllocator::my_free(void *ptr){

        std::lock_guard<std::mutex>lock(allocator_mutex);
        if(ptr == nullptr){
            std::cout<<"[Error :] Null Pointer cannot be accepted back\n";
        }
        Block *block = (Block *)((unsigned char *)ptr - sizeof(Block));

        if(block->canary != CANARY_VALUE){
            std::cout<<"[Error :] Corrupted memory reinitialising memory pool\n";
            init_memory();
            return;
        }

        block->next = nullptr;

        if(this->front == nullptr){
            this->front = this->rear = block;
        }
        else{
            this->rear->next = block;
            this->rear = block;
        }
    }

    FixedBlockAllocator::~FixedBlockAllocator(void){
        this->front = nullptr;
        this->rear = nullptr;
    }
}
