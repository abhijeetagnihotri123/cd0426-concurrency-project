#include "control_loop.hpp"

namespace sensor_data_consumer{

    void consumer_sensor(Memory_Allocator::FixedBlockAllocator *fa , sensor_queue &queue , std::atomic<bool>&running){
        while(running.load()){
            auto next_wake = std::chrono::high_resolution_clock::now() + std::chrono::milliseconds(100);
            adas::SensorFrame *frame = queue.pop(sensor_data_consumer::time_out);
            if(frame != nullptr){
                std::cout<<*(frame)<<std::endl;
                fa->my_free((void *)frame);
            }
            std::this_thread::sleep_until(next_wake);
        }
    }
}