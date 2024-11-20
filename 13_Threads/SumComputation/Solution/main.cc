#include <algorithm>
#include <future>
#include <iostream>
#include <numeric>
#include <thread>
#include <vector>

#include "Timer.hpp"
#include "lib.h"
#include "utils.hpp" // dont forget the include setting for the c++ runner

int main()
{
    std::vector<std::int32_t> vector(NUM_ELEMENTS, 0);
    random_vector(vector);

    auto time1 = 0.0;
    volatile auto sum1 = 0;
    for (std::uint32_t i = 0; i < NUM_RUNS; ++i)
    {
        cpptiming::Timer t1;
        sum1 = range_sum_asyn<std::int32_t>(vector.begin(), vector.end());
        time1 += t1.elapsed_time<cpptiming::millisecs, double>();
    }
    std::cout << "Mean Async: " << time1 / NUM_RUNS << "ms sum: " << sum1
              << '\n';

    auto time2 = 0.0;
    volatile auto sum2 = 0;
    for (std::uint32_t i = 0; i < NUM_RUNS; ++i)
    {
        cpptiming::Timer t2;
        sum2 = parallel_sum_omp(vector);
        time2 += t2.elapsed_time<cpptiming::millisecs, double>();
    }
    std::cout << "Mean OpenMP: " << time2 / NUM_RUNS << "ms sum: " << sum2
              << '\n';

    return 0;
}
