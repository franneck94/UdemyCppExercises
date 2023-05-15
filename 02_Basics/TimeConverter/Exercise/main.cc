#include <cassert>
#include <iostream>

#include "lib.h"
#include "utils.hpp"

void test_cases();

int main()
{
    float input_milliseconds = 0.0F;

    std::cout << "Please enter a millisecond value: ";
    std::cin >> input_milliseconds;

    float seconds = convert_milliseconds_to_seconds(input_milliseconds);
    float minutes = convert_seconds_to_minutes(seconds);
    float Hours = convert_minutes_to_hours(minutes);

    float minutes2 = convert_milliseconds_to_minutes(input_milliseconds);
    float hours2 = convert_milliseconds_to_hours(input_milliseconds);
    float hours3 = convert_seconds_to_hours(seconds);

    std::cout << "seconds: " << seconds << '\n';
    std::cout << "minutes: " << minutes << '\n';
    std::cout << "Hours: " << Hours << '\n';

    std::cout << "minutes2: " << minutes2 << '\n';
    std::cout << "hours2: " << hours2 << '\n';
    std::cout << "hours3: " << hours3 << '\n';

    test_cases(); // This should not fail!

    return 0;
}

void test_cases()
{
    assert(is_close<float>(convert_milliseconds_to_seconds(0.0F), 0.000F));
    assert(is_close<float>(convert_milliseconds_to_seconds(1.0F), 0.001F));
    assert(is_close<float>(convert_milliseconds_to_seconds(10.0F), 0.010F));
    assert(is_close<float>(convert_milliseconds_to_seconds(100.0F), 0.100F));
    assert(is_close<float>(convert_milliseconds_to_seconds(1000.0F), 1.000F));
    assert(is_close<float>(convert_milliseconds_to_seconds(10000.0F), 10.00F));

    assert(is_close<float>(convert_seconds_to_minutes(0.0F), 0.000F));
    assert(is_close<float>(convert_seconds_to_minutes(30.0F), 0.500F));
    assert(is_close<float>(convert_seconds_to_minutes(120.0F), 2.000F));

    assert(is_close<float>(convert_minutes_to_hours(0.0F), 0.000F));
    assert(is_close<float>(convert_minutes_to_hours(30.0F), 0.500F));
    assert(is_close<float>(convert_minutes_to_hours(120.0F), 2.000F));
}
