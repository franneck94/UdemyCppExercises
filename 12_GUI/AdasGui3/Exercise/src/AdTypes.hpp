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

struct VehicleType
{
    std::int32_t id;
    LaneAssociationType lane;
    float speed_mps;
    float distance_m;
};

struct NeighborVehiclesType
{
    std::array<VehicleType, NUM_VEHICLES_ON_LANE> vehicles_left_lane;
    std::array<VehicleType, NUM_VEHICLES_ON_LANE> vehicles_center_lane;
    std::array<VehicleType, NUM_VEHICLES_ON_LANE> vehicles_right_lane;
};

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
        (void)x;
        return 0.0F; // TODO
    }
};

struct LaneInformationType
{
    Polynomial3rdDegreeType left_polynomial;
    Polynomial3rdDegreeType right_polynomial;

    /**
     * @brief To compute the middle point of the two polynomials at pos. x
     */
    float get_lateral_position(const float x) const
    {
        (void)x;
        return 0.0F; // TODO
    }
};

struct LanesInformationType
{
    LaneInformationType left_lane;
    LaneInformationType center_lane;
    LaneInformationType right_lane;
};
