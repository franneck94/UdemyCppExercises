#pragma once

#include <array>

#include "AdTypes.hpp"
#include "DataLoaderConstants.hpp"

struct EgoVehicleLogData
{
    std::array<LaneAssociationType, NUM_ITERATIONS> lanes;
    std::array<float, NUM_ITERATIONS> long_velocities_mps;
    std::array<float, NUM_ITERATIONS> lat_velocities_mps;
    std::array<float, NUM_ITERATIONS> velocities_mps;
    std::array<float, NUM_ITERATIONS> accelerations_mps2;
    std::array<float, NUM_ITERATIONS> heading_degs;
};

struct VehicleLogData
{
    std::int32_t id;
    ObjectClassType object_class;
    float width_m;
    float height_m;

    std::array<LaneAssociationType, NUM_ITERATIONS> lanes;
    std::array<float, NUM_ITERATIONS> long_velocities_mps;
    std::array<float, NUM_ITERATIONS> lat_velocities_mps;
    std::array<float, NUM_ITERATIONS> velocities_mps;
    std::array<float, NUM_ITERATIONS> accelerations_mps2;
    std::array<float, NUM_ITERATIONS> heading_degs;
    std::array<float, NUM_ITERATIONS> long_distances_m;
    std::array<float, NUM_ITERATIONS> lat_distances_m;
    std::array<float, NUM_ITERATIONS> rel_velocities_mps;
    std::array<float, NUM_ITERATIONS> rel_accelerations_mps2;
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

    std::array<float, NUM_ITERATIONS> lane_widths_m;
    std::array<LaneClassType, NUM_ITERATIONS> lane_classes;
};

using LanesLogData = std::array<LaneLogData, NUM_LANES>;
