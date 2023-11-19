#pragma once

#include <algorithm>
#include <array>
#include <cstddef>
#include <cstdint>

constexpr static std::size_t NUM_ENTRIES = 3;
constexpr static std::uint32_t TIME_SPAN_MS = 50;

void compute_velocities(
    const std::array<float, NUM_ENTRIES> long_velocities_mps,
    const std::array<float, NUM_ENTRIES> lat_velocities_mps,
    std::array<float, NUM_ENTRIES> &velocities_mps);

void compute_heading_degrees(
    const std::array<float, NUM_ENTRIES> long_velocities_mps,
    const std::array<float, NUM_ENTRIES> lat_velocities_mps,
    std::array<float, NUM_ENTRIES> &heading_degrees);

void compute_accelerations(const std::array<float, NUM_ENTRIES> &velocities_mps,
                           std::array<float, NUM_ENTRIES> &accelerations_mps2);

void compute_rel_velocities(
    const std::array<float, NUM_ENTRIES> &velocities_mps,
    const std::array<float, NUM_ENTRIES> &ego_velocities_mps,
    std::array<float, NUM_ENTRIES> &rel_velocities_mps);

void compute_rel_accelerations(
    const std::array<float, NUM_ENTRIES> &accelerations_mps2,
    const std::array<float, NUM_ENTRIES> &ego_accelerations_mps2,
    std::array<float, NUM_ENTRIES> &rel_accelerations_mps2);
