#ifndef SENSOR_PRODUCERS_ENHANCED_HPP
#define SENSOR_PRODUCERS_ENHANCED_HPP


#include "sensor_queue_lockfree.hpp"
#include "FixedBlockAllocator_LockFree.hpp"

namespace sensor_data_producers_enhanced{

    void lidar_producers_lf(Memory_Allocator_LockFree::FixedBlockAllocator_LockFree* , sensor_queue_lockfree & , std::atomic<bool>&);
    void radar_producers_lf(Memory_Allocator_LockFree::FixedBlockAllocator_LockFree* , sensor_queue_lockfree & , std::atomic<bool>&);
    void camera_producers_lf(Memory_Allocator_LockFree::FixedBlockAllocator_LockFree* , sensor_queue_lockfree & , std::atomic<bool>&);

}

#endif