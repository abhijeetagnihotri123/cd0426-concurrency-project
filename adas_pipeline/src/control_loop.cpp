#include "control_loop.hpp"

namespace sensor_data_consumer{

    void consumer_sensor(sensor_queue &queue , std::atomic<bool>&running){

        while(running.load()){
            adas::SensorFrame *frame = queue.pop(sensor_data_consumer::time_out);
            if(frame != nullptr){
                std::cout<<*(frame)<<std::endl;
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(20));
        }

    }

}