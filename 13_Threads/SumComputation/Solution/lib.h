#pragma once

#include <algorithm>
#include <cstdint>
#include <iterator>
#include <random>

constexpr static std::uint32_t NUM_THREADS = 8;
constexpr static std::uint32_t NUM_RUNS = 1'000;
constexpr static std::uint32_t NUM_ELEMENTS = 30'000'000;
constexpr static std::uint32_t ELEMENTS_THRESHOLD = 5'000'000;

/** START GIVEN FUNCTIONS **/
template <typename T>
T parallel_sum_omp(std::vector<T> &vec)
{
    T final_sum = 0;
    T local_sum = 0;

    std::uint32_t i = 0;
    const auto n = static_cast<std::uint32_t>(vec.size());

#pragma omp parallel for reduction(+ : local_sum) num_threads(NUM_THREADS)
    for (i = 0; i < n; ++i)
    {
        local_sum = local_sum + vec[i];
    }
#pragma omp critical
    {
        final_sum += local_sum;
    }

    return final_sum;
}
/** END GIVEN FUNCTIONS **/

template <typename T, typename RandomIter>
T range_sum_asyn(RandomIter start, RandomIter stop)
{
    const auto length = std::distance(start, stop);

    if (length < ELEMENTS_THRESHOLD)
    {
        return std::accumulate(start, stop, T{});
    }

    auto mid = start + length / 2;

    auto handle = std::async(std::launch::async,
                             range_sum_asyn<T, RandomIter>,
                             mid,
                             stop);

    const auto sum = range_sum_asyn<T, RandomIter>(start, mid);

    return sum + handle.get();
}
