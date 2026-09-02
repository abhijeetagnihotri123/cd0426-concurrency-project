#include "control_loop.hpp"

namespace sensor_data_consumer{

    void consumer_sensor(Memory_Allocator::FixedBlockAllocator *fa , sensor_queue &queue , std::atomic<bool>&running){
        
        constexpr float CRITICAL_TTC_THRESHOLD = 6.6f;
        constexpr auto STALE_THRESHOLD = std::chrono::milliseconds(75);
        
        while(running.load()){
            auto next_wake = std::chrono::high_resolution_clock::now() + std::chrono::milliseconds(20);
            adas::SensorFrame *frame = queue.pop(sensor_data_consumer::time_out);
            if(frame != nullptr){
                std::cout<<*(frame);

                auto time_now = std::chrono::high_resolution_clock::now();
                auto difference = std::chrono::duration_cast<std::chrono::milliseconds>(time_now - frame->time_now);

                if(difference > STALE_THRESHOLD){
                    std::cout << "[WARN] Dropped Stale Frame | ID: " << frame->frame_id 
                          << " | Age: " << difference.count() << "ms\n";
                    fa->my_free((void *)frame); 
                    std::this_thread::sleep_until(next_wake);
                    continue;
                }
                
                if(frame->type == adas::SensorType::Radar || frame->type == adas::SensorType::LiDar){

                    if(frame->distance <= 0.0 || frame->distance >= 250.0f){
                        std::cout<<"[ERROR] corrupted distance recorded from sensor\n";
                    }
                    else{
                        frame->relative_velocity = std::abs(frame->relative_velocity);
                        float ttc = (frame->distance/frame->relative_velocity);

                        if (ttc <= CRITICAL_TTC_THRESHOLD) {
                        std::cout << "[EMERGENCY BRAKE] "
                                  << (frame->type == adas::SensorType::LiDar ? "LiDAR" : "Radar")
                                  << " Frame #" << frame->frame_id
                                  << " | Dist: " << frame->distance << "m"
                                  << " | TTC: " << ttc << "s\n";
                        } 
                        else {
                            std::cout << "[INFO] Target tracked | Dist: " << frame->distance 
                                    << "m | TTC: " << ttc << "s\n";
                        }
                    }
                }

                else if(frame->type == adas::SensorType::Camera){
                    float speed_limit = frame->relative_velocity; 
                    if (speed_limit < 10.0f || speed_limit > 140.0f) {
                        std::cout << "[WARN] Corrupted Speed Limit Sign Dropped: " << speed_limit << " km/h\n";
                    } else {
                        std::cout << "[CONTROL] Cruise Speed set to: " << speed_limit << " km/h\n";
                    }
                }

                fa->my_free((void *)frame);
            }
            std::this_thread::sleep_until(next_wake);
        }
    }

    void consumer_sensor_lf(Memory_Allocator::FixedBlockAllocator *fa , sensor_queue_lockfree &queue , std::atomic<bool>&running){
        
        constexpr float CRITICAL_TTC_THRESHOLD = 6.6f;
        constexpr auto STALE_THRESHOLD = std::chrono::milliseconds(75);
        
        while(running.load()){
            auto next_wake = std::chrono::high_resolution_clock::now() + std::chrono::milliseconds(20);
            adas::SensorFrame *frame = queue.pop();
            if(frame != nullptr){
                std::cout<<*(frame);

                auto time_now = std::chrono::high_resolution_clock::now();
                auto difference = std::chrono::duration_cast<std::chrono::milliseconds>(time_now - frame->time_now);

                if(difference > STALE_THRESHOLD){
                    std::cout << "[WARN] Dropped Stale Frame | ID: " << frame->frame_id 
                          << " | Age: " << difference.count() << "ms\n";
                    fa->my_free((void *)frame); 
                    std::this_thread::sleep_until(next_wake);
                    continue;
                }
                
                if(frame->type == adas::SensorType::Radar || frame->type == adas::SensorType::LiDar){

                    if(frame->distance <= 0.0 || frame->distance >= 250.0f){
                        std::cout<<"[ERROR] corrupted distance recorded from sensor\n";
                    }
                    else{
                        frame->relative_velocity = std::abs(frame->relative_velocity);
                        float ttc = (frame->distance/frame->relative_velocity);

                        if (ttc <= CRITICAL_TTC_THRESHOLD) {
                        std::cout << "[EMERGENCY BRAKE] "
                                  << (frame->type == adas::SensorType::LiDar ? "LiDAR" : "Radar")
                                  << " Frame #" << frame->frame_id
                                  << " | Dist: " << frame->distance << "m"
                                  << " | TTC: " << ttc << "s\n";
                        } 
                        else {
                            std::cout << "[INFO] Target tracked | Dist: " << frame->distance 
                                    << "m | TTC: " << ttc << "s\n";
                        }
                    }
                }

                else if(frame->type == adas::SensorType::Camera){
                    float speed_limit = frame->relative_velocity; 
                    if (speed_limit < 10.0f || speed_limit > 140.0f) {
                        std::cout << "[WARN] Corrupted Speed Limit Sign Dropped: " << speed_limit << " km/h\n";
                    } else {
                        std::cout << "[CONTROL] Cruise Speed set to: " << speed_limit << " km/h\n";
                    }
                }

                fa->my_free((void *)frame);
            }
            std::this_thread::sleep_until(next_wake);
        }
    }


}