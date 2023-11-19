#include <cstdint>

#include "lib.h"

std::uint32_t modulo(const std::uint32_t number_a, const std::uint32_t number_b)
{
    if (number_b == 0)
    {
        return 0;
    }

    std::uint32_t result = 0;
    std::uint32_t divisor = number_a / number_b;

    result = number_a - number_b * divisor;

    return result;
}

std::uint32_t sum_of_digits(std::uint32_t number)
{
    std::uint32_t num_digits = 0;

    do
    {
        number /= 10;
        num_digits++;
    } while (number > 0);

    return num_digits;
}

std::uint32_t cross_sum(std::uint32_t number)
{
    std::uint32_t sum = 0;

    while (number > 0)
    {
        std::uint32_t current_digit = number % 10;

        sum += current_digit;

        number /= 10;
    }

    return sum;
}
