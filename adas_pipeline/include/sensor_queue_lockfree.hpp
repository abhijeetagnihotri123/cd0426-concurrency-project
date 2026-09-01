#ifndef SENSOR_QUEUE_LOCKFREE_HPP
#define SENSOR_QUEUE_LOCKFREE_HPP

#include "sensor_frame.hpp"

#include <array>
#include <atomic>

#define EMPTY_BUFFER_INDEX_LF 0
#define EMPTY_BUFFER_SIZE_LF 0

class sensor_queue_lockfree{

private:
    static constexpr int capacity = 16;
    std::array<adas::SensorFrame* , capacity>buffer{};

    std::atomic<size_t>front_{EMPTY_BUFFER_INDEX_LF};
    std::atomic<size_t>rear_{EMPTY_BUFFER_INDEX_LF};
    std::atomic<size_t>num_elements{EMPTY_BUFFER_SIZE_LF};

public:

    sensor_queue_lockfree() = default;
    ~sensor_queue_lockfree() = default;

    bool push(adas::SensorFrame*);
    adas::SensorFrame* pop(void); //timeout no longer needed as it is lockfree
    void display_queue(void);

};

#endif