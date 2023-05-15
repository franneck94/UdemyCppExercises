# Exercise

Note: Based on Chapter 13 in the main course.

```cpp
#include "utils.hpp"
#include "Timer.hpp"

template <typename RandomIter>
auto range_sum_asyn(RandomIter start, RandomIter stop)
```

Implement an async function that computes the sum of a vector in the range of the **start** and **stop** iterator.  
The function should launch several tasks within an async context by calling itself recursively.

E.g.

```cpp
std::async(std::launch::async, range_sum_asyn<RandomIter>, mid, stop);
```

Pseudo-code:

1. If Length from *start* to *stop* is below THRESHOLD => call accumulate for 
2. Else call the function recursively by dividing the [start, stop) range in two halves
3. Repeat 1. - 2.

## Main Function

```cpp
int main()
{
    std::vector<std::int32_t> vector(30'000'000, 0);
    random_vector(vector);

    auto time1 = 0.0;
    volatile auto sum1 = 0;
    for (std::uint32_t i = 0; i < NUM_RUNS; ++i)
    {
        cpptiming::Timer t1;
        sum1 = range_sum_asyn<std::int32_t>(vector.begin(), vector.end());
        time1 += t1.elapsed_time<cpptiming::millisecs, double>();
    }
    std::cout << "Mean Async: " << time1 / NUM_RUNS << "ms sum: " << sum1 << '\n';

    return 0;
}
```
