#include <cstdint>
#include <iostream>

#include "lib.h"

double calculate_pi(const std::uint32_t num_iterations)
{
    double result = 0.0;

    for (std::uint32_t n = 0; n < num_iterations; n++)
    {
        result += (1.0 / (4.0 * n + 1.0)) - (1.0 / (4.0 * n + 3.0));
    }

    return result * 4.0;
}

void print_dec_to_bin(std::uint8_t value)
{
    std::cout << "Binary: 0b";

    for (std::int8_t i = 7; i >= 0; i--)
    {
        std::uint8_t current_exponent =
            static_cast<std::uint8_t>(std::pow(2, i));

        if (current_exponent <= value)
        {
            std::cout << "1";
            value -= current_exponent;
        }
        else
        {
            std::cout << "0";
        }
    }

    std::cout << "\n";
}
