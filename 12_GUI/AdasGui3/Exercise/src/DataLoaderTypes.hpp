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

struct LaneLogData
{
    LaneAssociationType lane;
    std::array<Polynomial3rdDegreeType, NUM_ITERATIONS> left_polynomials;
    std::array<Polynomial3rdDegreeType, NUM_ITERATIONS> right_polynomials;
};

using LanesLogData = std::array<LaneLogData, NUM_LANES>;
