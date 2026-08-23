#ifndef FIXED_BLOCK_ALLOCATOR_HPP
#define FIXED_BLOCK_ALLOCATOR_HPP

#include <stdint.h>
#include <mutex>

#define TOTAL_SIZE (1 << 15)
#define CANARY_VALUE 0x7a3f81e2b4d96c00

namespace Memory_Allocator{

    class FixedBlockAllocator{

        private:
            alignas(16) unsigned char pool[TOTAL_SIZE];
            struct Block{
                Block *next;
                uint64_t canary; 
            };
            Block *front{nullptr};
            Block *rear{nullptr};
            std::mutex allocator_mutex;
        
        public:
            FixedBlockAllocator(void);
            
            void init_memory(void);
            void *my_malloc(void);
            void my_free(void);
            FixedBlockAllocator(const FixedBlockAllocator &) = delete;
            FixedBlockAllocator& operator=(const FixedBlockAllocator&) = delete;
            ~FixedBlockAllocator(void);
    };
}

#endif