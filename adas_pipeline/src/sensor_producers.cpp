#include "sensor_producers.hpp"

namespace sensor_data_producers{
 
    void lidar_producers(sensor_queue &queue , std::atomic<bool>&running){

        int id = 0;
        while(running.load()){
            adas::SensorFrame *frame = new adas::SensorFrame;
            auto next_wake = std::chrono::high_resolution_clock::now() + std::chrono::milliseconds(100);
            frame->type = adas::SensorType::LiDar;
            frame->distance = 50.5;
            frame->relative_velocity = 121.9;
            frame->time_now = std::chrono::high_resolution_clock::now();
            frame->frame_id = id++; 
            queue.push(frame);
            std::this_thread::sleep_until(next_wake);
        }
    }

    void radar_producers(sensor_queue &queue , std::atomic<bool>&running){

        int id = 0;
        while(running.load()){
            adas::SensorFrame *frame = new adas::SensorFrame;
            auto next_wake = std::chrono::high_resolution_clock::now() + std::chrono::milliseconds(80);
            frame->type = adas::SensorType::Radar;
            frame->distance = 90.9;
            frame->relative_velocity = 119.1;
            frame->time_now = std::chrono::high_resolution_clock::now();
            frame->frame_id = id++;
            queue.push(frame);
            std::this_thread::sleep_until(next_wake);
        }
    }

    void camera_producers(sensor_queue &queue , std::atomic<bool>&running){

        int id = 0;
        while(running.load()){
            adas::SensorFrame *frame = new adas::SensorFrame;
            auto next_wake = std::chrono::high_resolution_clock::now() + std::chrono::milliseconds(60);
            frame->type = adas::SensorType::Camera;
            frame->distance = 200.11;
            frame->relative_velocity = 44.5;
            frame->time_now = std::chrono::high_resolution_clock::now();
            frame->frame_id = id++;
            queue.push(frame);
            std::this_thread::sleep_until(next_wake);
        }
    }
}