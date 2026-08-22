#include "sensor_queue.hpp"
#include "sensor_producers.hpp"
#include "control_loop.hpp"


int main(){

    std::atomic<bool>running;
    running.store(true);

    sensor_queue queue;

    std::thread t1(sensor_data_producers::lidar_producers , std::ref(queue) , std::ref(running));
    std::thread t2(sensor_data_producers::radar_producers , std::ref(queue) , std::ref(running));
    std::thread t3(sensor_data_producers::camera_producers, std::ref(queue) , std::ref(running));
    std::thread t4(sensor_data_consumer::consumer_sensor  , std::ref(queue) , std::ref(running));

    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    running.store(false);

    t1.join();
    t2.join();
    t3.join();
    t4.join();

    std::cout<<"Graceful shutdown of adas system\n";

    return 0;
}


#if 0
int main(){

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

            std::cout<<queue.push(&frame)<<std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
        }

    });

    std::thread t2([&queue](){
        while(!stop){
//            std::cout<<*(queue.pop(time_out))<<std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
        }
    });

    std::this_thread::sleep_for(std::chrono::milliseconds(2000));

    std::thread t3(set_stop);

    t1.join();
    t2.join();
    t3.join();


    return 0;
}
#endif
