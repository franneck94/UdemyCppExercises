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
        return std::pow(a, 3.0F) * x + std::pow(b, 2.0F) * x + std::pow(c, 1.0F) * x + d;
    }
};

enum class LaneBoundaryType
{
    DASHED,
    SOLID,
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

    /**
     * @brief To compute the middle point of the two polynomials at pos. x
     */
    float get_lateral_position(const float x) const
    {
        if (x < 0.0F)
        {
            return (left_polynomial.d + right_polynomial.d) / 2.0F;
        }
        else
        {
            return (left_polynomial(x) + right_polynomial(x)) / 2.0F;
        }
    }
};

struct LanesInformationType
{
    LaneInformationType left_lane;
    LaneInformationType center_lane;
    LaneInformationType right_lane;
};
