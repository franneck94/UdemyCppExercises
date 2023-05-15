#include <cassert>
#include <cfloat>
#include <cmath>
#include <iomanip>
#include <iostream>

#include "lib.h"

void test_cases();

int main()
{
    std::uint32_t num_iterations = 1'000'000;
    double pi = 3.14159265358979323846;
    double pi_calculated = calculate_pi(num_iterations);

    std::cout << std::setprecision(30);
    std::cout << "pi (calculated): " << pi_calculated << '\n';
    std::cout << "pi (correct): " << pi << '\n';

    std::uint8_t dec = 0b10001110;
    print_dec_to_bin(dec);

    test_cases(); // This should not fail!
}

void test_cases()
{
    const auto diff =
        std::fabs(calculate_pi(1'000'000) - 3.14159265358979323846);
    assert(diff < 1e-04);
}
