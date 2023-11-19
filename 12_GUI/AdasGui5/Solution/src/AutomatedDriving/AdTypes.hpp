#pragma once

#include <array>
#include <cmath>
#include <cstdint>

#include "AdConstants.hpp"

enum class LaneAssociationType
{
    LEFT,
    CENTER,
    RIGHT,
    NONE,
};

enum class ObjectClassType
{
    CAR,
    TRUCK,
    MOTORBIKE,
    NONE,
};

struct VehicleInformationType
{
    std::int32_t id;
    ObjectClassType object_class;
    float width_m;
    float height_m;

    LaneAssociationType lane;
    float velocity_mps;
    float long_distance_m;
    float lat_distance_m;
};

using NeighborVehiclesType = std::array<VehicleInformationType, MAX_NUM_VEHICLES>;

struct Polynomial3rdDegreeType
{
    float a;
    float b;
    float c;
    float d;

    /**
     * @brief To compute p(x) = a^3 * x + b^2 * x + c * x + d
     */
    float operator()(const float x) const
    {
        return std::pow(a, 3.0F) * x + std::pow(b, 2.0F) * x + std::pow(c, 1.0F) * x + d;
    }
};

enum class LaneBoundaryType
{
    DASHED,
    SOLID,
    NONE,
};

enum class LaneClassType
{
    NORMAL,
    ACCELERATION,
    DECELERATION,
    HARD_SHOULDER,
    NONE,
};

struct LaneInformationType
{
    Polynomial3rdDegreeType left_polynomial;
    Polynomial3rdDegreeType right_polynomial;

    LaneBoundaryType left_boundary_type;
    LaneBoundaryType right_boundary_type;

    float left_view_range_m;
    float right_view_range_m;

    float lane_width_m;
    LaneClassType lane_class;
};

struct LanesInformationType
{
    LaneInformationType left_lane;
    LaneInformationType center_lane;
    LaneInformationType right_lane;
};
