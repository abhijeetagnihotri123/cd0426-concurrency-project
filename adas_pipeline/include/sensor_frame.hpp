#ifndef SENSOR_FRAME_HPP
#define SENSOR_FRAME_HPP

#include <cstdint>
#include <chrono>
#include <iostream>
#include <atomic>
#include <thread>

namespace adas{

    enum class SensorType{
        Camera = 0,
        LiDar,
        Radar
    };

    struct SensorFrame{
        SensorType type;
        uint64_t frame_id{0};
        std::chrono::high_resolution_clock::time_point time_now{};
        float distance;
        float relative_velocity;
        
        friend std::ostream &operator<<(std::ostream &out , const SensorFrame &sensor){

            out<<"{";

            if(sensor.type == SensorType::Radar){
                out<<"Radar ,";
            }
            if(sensor.type == SensorType::Camera){
                out<<"Camera ,";
            }
            if(sensor.type == SensorType::LiDar){
                out<<"LiDar ,";
            }
            
            auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(sensor.time_now.time_since_epoch());
            out<<sensor.frame_id<<" , "<<duration.count()<<" , "<<sensor.distance<<" , "<<sensor.relative_velocity<<"}\n";
            return out;
        }
    };

}

#endif