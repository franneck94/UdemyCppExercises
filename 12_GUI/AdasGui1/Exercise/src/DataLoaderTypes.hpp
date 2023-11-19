#pragma once

#include <array>

#include "AdTypes.hpp"
#include "DataLoaderConstants.hpp"

struct VehicleLogData
{
    std::int32_t id;
    LaneAssociationType lane;
    float start_distance_m;
    std::array<float, NUM_ITERATIONS> speeds_mps;
};

using VehiclesLogData = std::array<VehicleLogData, NUM_VEHICLES>;
