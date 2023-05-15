#include <cstddef>
#include <cstdint>
#include <vector>

#include "lib.h"

bool all_of(const std::vector<std::int32_t> &vector, const std::int32_t value)
{
    for (const auto &current_value : vector)
    {
        if (current_value != value)
        {
            return false;
        }
    }

    return true;
}

bool any_of(const std::vector<std::int32_t> &vector, const std::int32_t value)
{
    for (const auto &current_value : vector)
    {
        if (current_value == value)
        {
            return true;
        }
    }

    return false;
}

bool none_of(const std::vector<std::int32_t> &vector, const std::int32_t value)
{
    for (const auto &current_value : vector)
    {
        if (current_value == value)
        {
            return false;
        }
    }

    return true;
}

std::size_t count(const std::vector<std::int32_t> &vector,
                  const std::int32_t value)
{
    auto counter = std::size_t{0};

    for (const auto &current_value : vector)
    {
        if (current_value == value)
        {
            counter++;
        }
    }

    return counter;
}
