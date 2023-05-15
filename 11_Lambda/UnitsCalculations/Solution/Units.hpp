#pragma once

#include <cmath>
#include <type_traits>
#include <utility>

template <typename T>
constexpr T PI = T(3.14159265358979323846L);

template <typename T, typename U>
[[nodiscard]] constexpr U ms_to_s(const T ms)
{
    static_assert(
        std::conjunction_v<std::is_integral<T>, std::is_floating_point<U>>,
        "Invalid types.");

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
[[nodiscard]] constexpr std::pair<T, T> rotate_point(const T theta,
                                                     const T x,
                                                     const T y)
{
    static_assert(std::is_floating_point_v<T>, "Must be floating point type.");

    const auto c = std::cos(theta);
    const auto s = std::sin(theta);

    const auto x_s = x * c - y * s;
    const auto y_s = x * s + y * c;

    return {x_s, y_s};
}
