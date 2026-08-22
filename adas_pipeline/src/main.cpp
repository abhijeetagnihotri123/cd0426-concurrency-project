#include "sensor_queue.hpp"
#include <thread>

bool stop = false;

void set_stop(){
    stop = true;
}

const auto time_out = std::chrono::milliseconds(25);

int main(){

#if 0
    sensor_queue queue;

    std::thread t1([&queue](){

        uint64_t frame_id = 0;
        while(!stop){

            adas::SensorFrame frame = {
                .type = adas::SensorType::Camera,
                .frame_id = frame_id++,
                .time_now = std::chrono::high_resolution_clock::now(),
                .distance = 132.5,
                .relative_velocity = 12.2
            };

            std::cout<<queue.push(frame)<<std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
        }

    });

    std::thread t2([&queue](){
        while(!stop){
            std::cout<<queue.pop(time_out)<<std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
        }
    });

    std::this_thread::sleep_for(std::chrono::milliseconds(2000));

    std::thread t3(set_stop);

    t1.join();
    t2.join();
    t3.join();

#endif

    return 0;
}