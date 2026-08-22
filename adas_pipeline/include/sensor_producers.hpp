#ifndef SENSOR_PRODUCERS_HPP
#define SENSOR_PRODUCERS_HPP

#include "sensor_queue.hpp"

namespace sensor_data_producers{

    void lidar_producers(sensor_queue & , std::atomic<bool>&);
    void radar_producers(sensor_queue & , std::atomic<bool>&);
    void camera_producers(sensor_queue & , std::atomic<bool>&);

}

#endif