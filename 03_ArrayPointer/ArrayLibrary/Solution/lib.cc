#include <cstddef>
#include <cstdint>
#include <iostream>

#include "lib.h"

void remove_duplicates(std::int32_t *array, std::size_t &length)
{
    if (array == nullptr || length == 0)
    {
        return;
    }

    for (std::size_t i = 0; i < length; i++)
    {
        auto duplicate_index = static_cast<std::size_t>(-1);
        std::int32_t current_value = array[i];

        for (std::size_t j = i + 1; j < length; j++)
        {
            if (current_value == array[j])
            {
                duplicate_index = j;
                length--;
                break;
            }
        }

        if (duplicate_index == static_cast<std::size_t>(-1))
        {
            continue;
        }

        for (std::size_t j = duplicate_index; j < length; j++)
        {
            array[j] = array[j + 1];
        }

        array[length] = 0;
    }
}

void rotate_left(std::int32_t *array, std::size_t length)
{
    if (array == nullptr || length == 0)
    {
        return;
    }

    std::int32_t first_element = array[0];

    for (std::size_t i = 1; i < length; i++)
    {
        array[i - 1] = array[i];
    }

    array[length - 1] = first_element;
}

void rotate_right(std::int32_t *array, std::size_t length)
{
    if (array == nullptr || length == 0)
    {
        return;
    }

    std::int32_t last_element = array[length - 1];

    for (std::size_t i = length - 1; i > 0; i--)
    {
        array[i] = array[i - 1];
    }

    array[0] = last_element;
}
