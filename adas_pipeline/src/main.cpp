#include "sensor_queue.hpp"
#include "sensor_producers.hpp"
#include "control_loop.hpp"
#include "FixedBlockAllocator.hpp"

using namespace Memory_Allocator;
using namespace adas;

int main(){

    FixedBlockAllocator fa;

    SensorFrame *frame1 = (SensorFrame *)fa.my_malloc();
    SensorFrame *frame2 = (SensorFrame *)fa.my_malloc();
    SensorFrame *frame3 = (SensorFrame *)fa.my_malloc();
    SensorFrame *frame4 = (SensorFrame *)fa.my_malloc();
    SensorFrame *frame5 = (SensorFrame *)fa.my_malloc();

    frame1->type = SensorType::Camera;
    frame1->distance = 119.9;
    frame1->relative_velocity = 90.9;
    frame1->frame_id = 1;
    frame1->time_now = std::chrono::high_resolution_clock::now();

    std::cout<<*(frame1)<<std::endl;
    std::cout<<(frame1)<<std::endl;
    std::cout<<(frame2)<<std::endl;
    std::cout<<(frame3)<<std::endl;
    std::cout<<(frame4)<<std::endl;
    std::cout<<(frame5)<<std::endl;
    

    fa.my_free((void *)frame1);
    fa.my_free((void *)frame2);
    fa.my_free((void *)frame3);
    fa.my_free((void *)frame4);
    fa.my_free((void *)frame5);

    return 0;
}


#if 0

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


#endif