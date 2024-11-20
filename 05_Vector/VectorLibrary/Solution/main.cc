#include <cassert>
#include <cstdint>
#include <cstring>
#include <iostream>
#include <vector>

#include "lib.h"
#include "utils.hpp" // dont forget the include setting for the c++ runner

void test_cases();

int main()
{
    auto vector = std::vector<std::int32_t>{1, 1, 2, 3, 3, 4};

    std::cout << "remove_duplicates: " << '\n';
    remove_duplicates(vector);
    print_vector(vector);

    std::cout << "rotate_left: " << '\n';
    rotate_left(vector);
    print_vector(vector);

    std::cout << "rotate_right: " << '\n';
    rotate_right(vector);
    print_vector(vector);

    test_cases();

    return 0;
}

void test_cases()
{
    auto vec = std::vector<std::int32_t>{1, 1, 2, 3, 3, 4};
    auto vec_swap = std::vector<std::int32_t>{4, 1, 2, 3, 3, 1};
    auto vec_cpy = std::vector<std::int32_t>{1, 1, 2, 3, 3, 4};
    auto vec_del = std::vector<std::int32_t>{1, 2, 3, 4};

    rotate_left(vec_cpy);
    assert(vectors_are_same(vec, vec_cpy) == false);
    rotate_right(vec_cpy);
    assert(vectors_are_same(vec, vec_cpy) == true);

    remove_duplicates(vec_cpy);
    assert(vectors_are_same(vec_cpy, vec_del) == true);
    assert(vectors_are_same(vec, vec_del) == false);

    swap_boundary_values(vec);
    assert(vectors_are_same(vec, vec_swap) == true);
}
