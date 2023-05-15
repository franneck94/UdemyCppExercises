#include <cstdint>

#include "lib.h"

float convert_milliseconds_to_seconds(const float milliseconds)
{
    return milliseconds / 1000.0F;
}

float convert_seconds_to_minutes(const float seconds)
{
    return seconds / 60.0F;
}

float convert_minutes_to_hours(const float minutes)
{
    return minutes / 60.0F;
}

float convert_milliseconds_to_minutes(const float milliseconds)
{
    float seconds = convert_milliseconds_to_seconds(milliseconds);
    float minutes = convert_seconds_to_minutes(seconds);

    return minutes;
}

float convert_milliseconds_to_hours(const float milliseconds)
{
    float seconds = convert_milliseconds_to_seconds(milliseconds);
    float minutes = convert_seconds_to_minutes(seconds);
    float hours = convert_minutes_to_hours(minutes);

    return hours;
}

float convert_seconds_to_hours(const float seconds)
{
    float minutes = convert_seconds_to_minutes(seconds);
    float hours = convert_minutes_to_hours(minutes);

    return hours;
}
