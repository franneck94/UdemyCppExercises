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

    std::array<LaneBoundaryType, NUM_ITERATIONS> left_boundary_types;
    std::array<LaneBoundaryType, NUM_ITERATIONS> right_boundary_types;

    std::array<float, NUM_ITERATIONS> left_view_ranges_m;
    std::array<float, NUM_ITERATIONS> right_view_ranges_m;
};

using LanesLogData = std::array<LaneLogData, NUM_LANES>;
