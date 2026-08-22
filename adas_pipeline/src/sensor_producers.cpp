#include "sensor_producers.hpp"

namespace sensor_data_producers{
 
    void lidar_producers(sensor_queue &queue , std::atomic<bool>&running){

        int id = 0;
        while(running.load()){
            adas::SensorFrame *frame = new adas::SensorFrame;
            frame->type = adas::SensorType::LiDar;
            frame->distance = 50.5;
            frame->relative_velocity = 121.9;
            frame->time_now = std::chrono::high_resolution_clock::now();
            frame->frame_id = id++; 
            queue.push(frame);
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }

    }
    void radar_producers(sensor_queue &queue , std::atomic<bool>&running){

        int id = 0;
        while(running.load()){
            adas::SensorFrame *frame = new adas::SensorFrame;
            frame->type = adas::SensorType::Radar;
            frame->distance = 90.9;
            frame->relative_velocity = 119.1;
            frame->time_now = std::chrono::high_resolution_clock::now();
            frame->frame_id = id++;
            queue.push(frame);
            std::this_thread::sleep_for(std::chrono::milliseconds(80));
        }
    }
    void camera_producers(sensor_queue &queue , std::atomic<bool>&running){

        int id = 0;
        while(running.load()){
            adas::SensorFrame *frame = new adas::SensorFrame;
            frame->type = adas::SensorType::Camera;
            frame->distance = 200.11;
            frame->relative_velocity = 44.5;
            frame->time_now = std::chrono::high_resolution_clock::now();
            frame->frame_id = id++;
            queue.push(frame);
            std::this_thread::sleep_for(std::chrono::milliseconds(60));
        }
    }

}