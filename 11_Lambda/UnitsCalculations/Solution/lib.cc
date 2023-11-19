#include <algorithm>
#include <array>
#include <cmath>
#include <cstddef>
#include <cstdint>

#include "Units.hpp"
#include "lib.h"

void compute_velocities(
    const std::array<float, NUM_ENTRIES> long_velocities_mps,
    const std::array<float, NUM_ENTRIES> lat_velocities_mps,
    std::array<float, NUM_ENTRIES> &velocities_mps)
{
    std::transform(long_velocities_mps.begin(),
                   long_velocities_mps.end(),
                   lat_velocities_mps.begin(),
                   velocities_mps.begin(),
                   [&](const auto v_long, const auto v_lat) {
                       return std::sqrt(std::pow(v_long, 2.0F) +
                                        std::pow(v_lat, 2.0F));
                   });
}

void compute_heading_degrees(
    const std::array<float, NUM_ENTRIES> long_velocities_mps,
    const std::array<float, NUM_ENTRIES> lat_velocities_mps,
    std::array<float, NUM_ENTRIES> &heading_degrees)
{
    std::transform(long_velocities_mps.begin(),
                   long_velocities_mps.end(),
                   lat_velocities_mps.begin(),
                   heading_degrees.begin(),
                   [&](const auto v_long, const auto v_lat) {
                       return (std::atan2(v_lat, v_long) / PI<float>)*180.0F;
                   });
}

void compute_accelerations(const std::array<float, NUM_ENTRIES> &velocities_mps,
                           std::array<float, NUM_ENTRIES> &accelerations_mps2)
{
    accelerations_mps2[0] = 0.0F;

    for (std::size_t i = 1; i < NUM_ENTRIES; ++i)
    {
        accelerations_mps2[i] = (velocities_mps[i] - velocities_mps[i - 1]) /
                                ms_to_s<std::uint32_t, float>(TIME_SPAN_MS);
    }
}

void compute_rel_velocities(
    const std::array<float, NUM_ENTRIES> &velocities_mps,
    const std::array<float, NUM_ENTRIES> &ego_velocities_mps,
    std::array<float, NUM_ENTRIES> &rel_velocities_mps)
{
    std::transform(
        velocities_mps.begin(),
        velocities_mps.end(),
        ego_velocities_mps.begin(),
        rel_velocities_mps.begin(),
        [&](const auto v_veh, const auto v_ego) { return v_ego - v_veh; });
}

void compute_rel_accelerations(
    const std::array<float, NUM_ENTRIES> &accelerations_mps2,
    const std::array<float, NUM_ENTRIES> &ego_accelerations_mps2,
    std::array<float, NUM_ENTRIES> &rel_accelerations_mps2)
{
    std::transform(
        accelerations_mps2.begin(),
        accelerations_mps2.end(),
        ego_accelerations_mps2.begin(),
        rel_accelerations_mps2.begin(),
        [&](const auto a_veh, const auto a_ego) { return a_ego - a_veh; });
}
