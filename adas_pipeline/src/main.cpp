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