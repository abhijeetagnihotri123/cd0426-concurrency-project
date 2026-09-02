#ifndef CONTROL_LOOP_HPP
#define CONTROL_LOOP_HPP

#include "sensor_queue.hpp"
#include "sensor_queue_lockfree.hpp"
#include "FixedBlockAllocator.hpp"

namespace sensor_data_consumer{
    const auto time_out = std::chrono::milliseconds(25);
    void consumer_sensor(Memory_Allocator::FixedBlockAllocator* , sensor_queue & , std::atomic<bool>&);
    void consumer_sensor_lf(Memory_Allocator::FixedBlockAllocator* , sensor_queue_lockfree & , std::atomic<bool>&);
}

#endif