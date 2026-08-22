#ifndef SENSOR_QUEUE_HPP
#define SENSOR_QUEUE_HPP

#include "sensor_frame.hpp"

#include <mutex>
#include <condition_variable>
#include <array>

#define EMPTY_BUFFER_INDEX 0
#define EMPTY_BUFFER_SIZE 0

class sensor_queue{

private:
    static constexpr int capacity = 16;
    std::array<adas::SensorFrame* , capacity>buffer{};
    std::mutex mtx;
    std::condition_variable cv;

    size_t front{EMPTY_BUFFER_INDEX};
    size_t rear{EMPTY_BUFFER_INDEX};
    size_t size{EMPTY_BUFFER_SIZE};

public:
    sensor_queue() = default;
    ~sensor_queue() = default;

    bool push(adas::SensorFrame*);
    adas::SensorFrame* pop(std::chrono::milliseconds);
    void display_queue(void);
};

#endif