#pragma once

#include <cstdint>
#include <cstring>

#include "Units.hpp"

constexpr auto EGO_VEHICLE_ID = std::int32_t{-1};
constexpr auto NONE_VEHICLE_ID = std::int32_t{-2};
constexpr auto MAX_NUM_VEHICLES = std::size_t{6};
constexpr auto LONGITUDINAL_DIFFERENCE_PERCENTAGE = float{0.05F};
constexpr auto NUM_LANES = std::size_t{3};

constexpr auto EGO_VEHICLE_WIDTH_M = float{2.5F};
constexpr auto EGO_VEHICLE_HEIGHT_M = float{5.0F};

constexpr auto CYCLE_TIME_MS = std::int64_t{50};
constexpr auto CYCLE_TIME_S = ms_to_s<std::int64_t, float>(CYCLE_TIME_MS);
