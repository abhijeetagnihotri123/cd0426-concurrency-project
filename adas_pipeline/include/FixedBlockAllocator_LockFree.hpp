#ifndef FIXED_BLOCK_ALLOCATOR_LOCKFREE_HPP
#define FIXED_BLOCK_ALLOCATOR_LOCKFREE_HPP

#include "sensor_frame.hpp"

#define TOTAL_SIZE (1 << 15)
#define CANARY_VALUE 0x7a3f81e2b4d96c00

namespace Memory_Allocator_LockFree{

    class FixedBlockAllocator_LockFree{

        private:
            alignas(16) unsigned char pool[TOTAL_SIZE];
            struct Block{
                Block *next;
                uint64_t canary;
            };
            std::atomic<Block*>front_{nullptr};
            std::atomic<Block*>rear_{nullptr};
        
        public:
            FixedBlockAllocator_LockFree(void);
            
            void init_memory(void);
            void *my_malloc(void);
            void my_free(void *);

            FixedBlockAllocator_LockFree(const FixedBlockAllocator_LockFree&) = delete;
            FixedBlockAllocator_LockFree &operator=(const FixedBlockAllocator_LockFree&) = delete;

            ~FixedBlockAllocator_LockFree(void);
    };
}

#endif