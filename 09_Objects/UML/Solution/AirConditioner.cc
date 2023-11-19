#include <iostream>

#include "AirConditioner.h"

float AirConditioner::measure() const
{
    const auto measured_temp = get_rand_float(-20.0F, 25.0F);
    std::cout << "The measured temp is: " << measured_temp
              << " the target temp is: " << target_temp_cel << '\n';

    return measured_temp;
}

int AirConditioner::activate(const float _current_temp_cel)
{
    curr_temp_cel = _current_temp_cel;

    if (curr_temp_cel < -20.0F || curr_temp_cel > 45.0F)
        return -1;

    auto needed_duration_min =
        static_cast<int>(std::ceil(std::abs(curr_temp_cel - target_temp_cel)));

    if (curr_temp_cel > target_temp_cel)
    {
        cool(needed_duration_min);
    }
    else if (curr_temp_cel < target_temp_cel)
    {
        needed_duration_min *= 2;
        heat(needed_duration_min);
    }

    return needed_duration_min;
}

bool AirConditioner::heat(const int duration_min)
{
    for (int i = 0; i < duration_min; i++)
    {
        if (i % 2 != 0 && i > 0)
            curr_temp_cel += 1.0F;
        std::cout << "After: " << (i + 1)
                  << " minutes the temp is: " << curr_temp_cel << '\n';

        if (curr_temp_cel >= target_temp_cel)
            break;
    }

    return duration_min != 0;
}

bool AirConditioner::cool(const int duration_min)
{
    for (int i = 0; i < duration_min; i++)
    {
        curr_temp_cel -= 1.0F;
        std::cout << "After: " << (i + 1)
                  << " minutes the temp is: " << curr_temp_cel << '\n';

        if (curr_temp_cel <= target_temp_cel)
            break;
    }

    return duration_min != 0;
}
