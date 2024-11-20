#include <cassert>
#include <cstring>
#include <iostream>

#include "lib.h"
#include "utils.hpp" // dont forget the include setting for the c++ runner

void test_cases();

int main()
{
    std::size_t length = 6;
    std::int32_t array[]{1, 1, 2, 3, 3, 4};

    remove_duplicates(array, length);
    print_array(array, length);

    rotate_left(array, length);
    print_array(array, length);

    rotate_right(array, length);
    print_array(array, length);

    test_cases(); // This should not fail

    return 0;
}

void test_cases()
{
    std::size_t length = 6;
    std::int32_t array[]{1, 1, 2, 3, 3, 4};
    std::int32_t array_cpy[]{1, 1, 2, 3, 3, 4};
    std::int32_t array_del[]{1, 2, 3, 4};

    rotate_left(array_cpy, length);
    assert(ranges_are_same(array, array_cpy, length) == false);
    rotate_right(array_cpy, length);
    assert(ranges_are_same(array, array_cpy, length) == true);

    remove_duplicates(array_cpy, length);
    assert(ranges_are_same(array_cpy, array_del, length) == true);
    assert(ranges_are_same(array, array_del, length) == false);
}
