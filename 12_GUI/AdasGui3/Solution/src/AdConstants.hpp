#pragma once

#include <cstdint>
#include <cstring>

constexpr float VIEW_RANGE_M = 100.0F;
constexpr std::int32_t EGO_VEHICLE_ID = -1;
constexpr std::size_t NUM_VEHICLES_ON_LANE = 2;
constexpr float LONGITUDINAL_DIFFERENCE_PERCENTAGE = 0.05F;
constexpr std::size_t NUM_LANES = 3;

constexpr auto LEFT_LEFT_BORDER{-4.5F};
constexpr auto LEFT_RIGHT_BORDER{-1.5F};
constexpr auto CENTER_LEFT_BORDER{-1.5F};
constexpr auto CENTER_RIGHT_BORDER{1.5F};
constexpr auto RIGHT_LEFT_BORDER{1.5F};
constexpr auto RIGHT_RIGHT_BORDER{4.5F};
