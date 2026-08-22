#ifndef CONTROL_LOOP_HPP
#define CONTROL_LOOP_HPP

#include "sensor_queue.hpp"

namespace sensor_data_consumer{
    const auto time_out = std::chrono::milliseconds(25);
    void consumer_sensor(sensor_queue & , std::atomic<bool>&);
}

#endif