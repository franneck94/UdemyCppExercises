#include <cassert>
#include <cstdint>
#include <iostream>

#include "lib.h"
#include "utils.hpp"

void test_cases();

int main()
{
    const std::int32_t array[]{3, 1, 4, 1, 5, 9, 2, 6};
    const std::size_t length = 8;

    std::cout << std::boolalpha;
    std::cout << "all_of: " << all_of(array, length, 5) << '\n';
    std::cout << "any_of: " << any_of(array, length, 5) << '\n';
    std::cout << "none_of: " << none_of(array, length, 5) << '\n';
    std::cout << "count: " << count(array, length, 1) << '\n';

    test_cases(); // This should not fail!

    return 0;
}

void test_cases()
{
    const std::int32_t array[]{2, 1, -2, 0, -1};
    const std::int32_t array_all[]{2, 2, 2, 2, 2};
    const std::size_t length = 5;

    assert(all_of(array_all, length, 2) == true);

    assert(all_of(nullptr, length, 2) == false);
    assert(any_of(nullptr, length, 2) == false);
    assert(none_of(nullptr, length, 2) == false);

    assert(all_of(array, 0, 2) == false);
    assert(any_of(array, 0, 2) == false);
    assert(none_of(array, 0, 2) == false);

    assert(count(array, length, 1) == 1);
    assert(count(array, length, -3) == 0);

    assert(any_of(array, length, 2) == true);
    assert(any_of(array, length, 1) == true);
    assert(any_of(array, length, 0) == true);
    assert(any_of(array, length, -1) == true);
    assert(any_of(array, length, -2) == true);

    assert(none_of(array, length, 3) == true);
    assert(none_of(array, length, 2) == false);
    assert(none_of(array, length, 1) == false);
    assert(none_of(array, length, 0) == false);
    assert(none_of(array, length, -1) == false);
    assert(none_of(array, length, -2) == false);
    assert(none_of(array, length, -3) == true);
}
