#pragma once

#include <cstdint>

#include "AdConstants.hpp"

enum class LaneAssociationType
{
    LEFT,
    CENTER,
    RIGHT,
    NONE,
};

struct VehicleType
{
    std::int32_t id;
    LaneAssociationType lane;
    float speed_mps;
    float distance_m;
};

struct NeighborVehiclesType
{
    VehicleType vehicles_left_lane[NUM_VEHICLES_ON_LANE];
    VehicleType vehicles_center_lane[NUM_VEHICLES_ON_LANE];
    VehicleType vehicles_right_lane[NUM_VEHICLES_ON_LANE];
};
