#include <algorithm>
#include <cassert>
#include <cstdint>
#include <cstring>
#include <iostream>
#include <vector>

#include "lib.h"
#include "utils.hpp"

void test_cases();

int main()
{
    auto vec1 = std::vector<std::int32_t>(5, 0);
    auto vec2 = std::vector<std::int32_t>(5, 0);
    std::cout << std::boolalpha
              << mystd::equal(vec1.begin(), vec1.end(), vec2.begin()) << '\n';

    mystd::fill_n(vec1.begin(), 5, 1);
    print_vector(vec1);

    mystd::iota(vec2.begin(), vec2.end(), 0);
    print_vector(vec2);
    std::cout << std::boolalpha
              << mystd::equal(vec1.begin(), vec1.end(), vec2.begin()) << '\n';

    mystd::copy(vec2.begin(), vec2.end(), vec1.begin());
    std::cout << std::boolalpha
              << mystd::equal(vec1.begin(), vec1.end(), vec2.begin()) << '\n';

    const auto sum = mystd::accumulate(vec1.begin(), vec1.end(), 0);
    std::cout << sum << '\n';

    test_cases();

    return 0;
}

void test_cases()
{
    auto vec1 = std::vector<std::int32_t>(5, 0);
    auto vec2 = std::vector<std::int32_t>(5, 0);
    auto vec3 = std::vector<std::int32_t>(5, 0);
    vec3.back() = 1;

    assert(mystd::equal(vec1.begin(), vec1.end(), vec2.begin()) == true);
    assert(mystd::equal(vec1.begin(), vec1.end(), vec3.begin()) == false);

    mystd::fill_n(vec1.begin(), 5, 1);
    mystd::fill_n(vec2.begin(), 5, 1);
    assert(mystd::equal(vec1.begin(), vec1.end(), vec2.begin()) == true);

    mystd::copy(vec1.begin(), vec1.end(), vec3.begin());
    assert(mystd::equal(vec1.begin(), vec1.end(), vec3.begin()) == true);

    assert(mystd::accumulate(vec1.begin(), vec1.end(), 0) == 5);
}
