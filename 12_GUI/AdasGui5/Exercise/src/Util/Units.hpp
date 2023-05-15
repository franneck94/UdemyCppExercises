#pragma once

#include <algorithm>
#include <array>
#include <cmath>
#include <type_traits>
#include <utility>

template <typename T>
constexpr T PI = T(3.14159265358979323846L);

template <typename T, typename U>
[[nodiscard]] constexpr U ms_to_s(const T ms)
{
    static_assert(std::conjunction_v<std::is_integral<T>, std::is_floating_point<U>>, "Invalid types.");

    return ms / static_cast<U>(1000.0);
}

template <typename T>
[[nodiscard]] constexpr T deg_to_rad(const T deg)
{
    static_assert(std::is_floating_point_v<T>, "Must be floating point type.");

    return deg * (PI<T> / static_cast<T>(180.0));
}

template <typename T>
[[nodiscard]] constexpr T kph_to_mps(const T kph)
{
    static_assert(std::is_floating_point_v<T>, "Must be floating point type.");

    return kph / static_cast<T>(3.6);
}

template <typename T>
[[nodiscard]] constexpr T mps_to_kph(const T mps)
{
    static_assert(std::is_floating_point_v<T>, "Must be floating point type.");

    return mps * static_cast<T>(3.6);
}

template <typename T>
void move_point(const T cx, const T cy, T &x, T &y)
{
    static_assert(std::is_floating_point_v<T>, "Must be floating point type.");

    x += cx;
    y += cy;
}

template <typename T>
[[nodiscard]] constexpr std::pair<T, T> rotate_point(const T theta, const T cx, const T cy, T x, T y)
{
    static_assert(std::is_floating_point_v<T>, "Must be floating point type.");

    move_point(-cx, -cy, x, y);

    const auto c = std::cos(theta);
    const auto s = std::sin(theta);

    auto x_s = x * c - y * s;
    auto y_s = x * s + y * c;

    move_point(cx, cy, x_s, y_s);

    return {x_s, y_s};
}

template <std::size_t N>
void compute_velocities(const std::array<float, N> long_velocities_mps,
                        const std::array<float, N> lat_velocities_mps,
                        std::array<float, N> &velocities_mps)
{
    std::transform(long_velocities_mps.begin(),
                   long_velocities_mps.end(),
                   lat_velocities_mps.begin(),
                   velocities_mps.begin(),
                   [&](const auto v_long, const auto v_lat) {
                       return std::sqrt(std::pow(v_long, 2.0F) + std::pow(v_lat, 2.0F));
                   });
}

template <std::size_t N>
void compute_heading_degrees(const std::array<float, N> long_velocities_mps,
                             const std::array<float, N> lat_velocities_mps,
                             std::array<float, N> &heading_degrees)
{
    std::transform(
        long_velocities_mps.begin(),
        long_velocities_mps.end(),
        lat_velocities_mps.begin(),
        heading_degrees.begin(),
        [&](const auto v_long, const auto v_lat) { return (std::atan2(v_lat, v_long) / PI<float>)*180.0F; });
}

template <std::size_t N>
void compute_accelerations(const std::array<float, N> &velocities_mps,
                           const std::uint32_t time_span_ms,
                           std::array<float, N> &accelerations_mps2)
{
    accelerations_mps2[0] = 0.0F;

    for (std::size_t i = 1; i < N; ++i)
    {
        accelerations_mps2[i] = (velocities_mps[i] - velocities_mps[i - 1]) / time_span_ms;
    }
}

template <std::size_t N>
void compute_rel_velocities(const std::array<float, N> &velocities_mps,
                            const std::array<float, N> &ego_velocities_mps,
                            std::array<float, N> &rel_velocities_mps)
{
    std::transform(velocities_mps.begin(),
                   velocities_mps.end(),
                   ego_velocities_mps.begin(),
                   rel_velocities_mps.begin(),
                   [&](const auto v_veh, const auto v_ego) { return v_ego - v_veh; });
}

template <std::size_t N>
void compute_rel_accelerations(const std::array<float, N> &accelerations_mps2,
                               const std::array<float, N> &ego_accelerations_mps2,
                               std::array<float, N> &rel_accelerations_mps2)
{
    std::transform(accelerations_mps2.begin(),
                   accelerations_mps2.end(),
                   ego_accelerations_mps2.begin(),
                   rel_accelerations_mps2.begin(),
                   [&](const auto a_veh, const auto a_ego) { return a_ego - a_veh; });
}
