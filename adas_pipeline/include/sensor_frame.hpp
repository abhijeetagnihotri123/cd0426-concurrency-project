#pragma once

#include <cstdint>
#include <chrono>

namespace adas{

    enum class SensorType{

        Camera = 0,
        LiDar,
        Radar

    };

    struct SensorFrame{
        SensorType type;
        uint64_t frame_id{0};
        std::chrono::high_resolution_clock::time_point time_now{};
        float distance;
        float relative_velocity;
    };

}
