#ifndef SENSOR_PRODUCERS_HPP
#define SENSOR_PRODUCERS_HPP

#include "sensor_queue.hpp"
#include "sensor_queue_lockfree.hpp"
#include "FixedBlockAllocator.hpp"

namespace sensor_data_producers{

    void lidar_producers(Memory_Allocator::FixedBlockAllocator* , sensor_queue & , std::atomic<bool>&);
    void radar_producers(Memory_Allocator::FixedBlockAllocator* , sensor_queue & , std::atomic<bool>&);
    void camera_producers(Memory_Allocator::FixedBlockAllocator* , sensor_queue & , std::atomic<bool>&);

    void lidar_producers_lf(Memory_Allocator::FixedBlockAllocator* , sensor_queue_lockfree & , std::atomic<bool>&);
    void radar_producers_lf(Memory_Allocator::FixedBlockAllocator* , sensor_queue_lockfree & , std::atomic<bool>&);
    void camera_producers_lf(Memory_Allocator::FixedBlockAllocator* , sensor_queue_lockfree & , std::atomic<bool>&);

}

#endif