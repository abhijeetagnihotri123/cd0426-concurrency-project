#include "sensor_producers.hpp"

namespace sensor_data_producers{
 
    void lidar_producers(Memory_Allocator::FixedBlockAllocator *fa , sensor_queue &queue , std::atomic<bool>&running){

        int id = 0;
        while(running.load()){
            // adas::SensorFrame *frame = new adas::SensorFrame;
            adas::SensorFrame *frame = (adas::SensorFrame*)fa->my_malloc();
            auto next_wake = std::chrono::high_resolution_clock::now() + std::chrono::milliseconds(500);
            if(frame != nullptr)
            {
                frame->type = adas::SensorType::LiDar;
                frame->distance = 50.5;
                frame->relative_velocity = 121.9;
                frame->time_now = std::chrono::high_resolution_clock::now();
                frame->frame_id = id++; 
                queue.push(frame);
            }
            std::this_thread::sleep_until(next_wake);
        }
    }

    void radar_producers(Memory_Allocator::FixedBlockAllocator *fa , sensor_queue &queue , std::atomic<bool>&running){

        int id = 0;
        while(running.load()){
            adas::SensorFrame *frame = (adas::SensorFrame*)fa->my_malloc();
            auto next_wake = std::chrono::high_resolution_clock::now() + std::chrono::milliseconds(400);
            if(frame != nullptr)
            {
                frame->type = adas::SensorType::Radar;
                frame->distance = 90.9;
                frame->relative_velocity = 119.1;
                frame->time_now = std::chrono::high_resolution_clock::now();
                frame->frame_id = id++;
                queue.push(frame);
            }
            std::this_thread::sleep_until(next_wake);
        }
    }

    void camera_producers(Memory_Allocator::FixedBlockAllocator *fa , sensor_queue &queue , std::atomic<bool>&running){

        int id = 0;
        while(running.load()){
            adas::SensorFrame *frame = (adas::SensorFrame*)fa->my_malloc();
            auto next_wake = std::chrono::high_resolution_clock::now() + std::chrono::milliseconds(300);
            if(frame != nullptr)
            {
                frame->type = adas::SensorType::Camera;
                frame->distance = 200.11;
                frame->relative_velocity = 44.5;
                frame->time_now = std::chrono::high_resolution_clock::now();
                frame->frame_id = id++;
                queue.push(frame);
            }
            std::this_thread::sleep_until(next_wake);
        }
    }
}