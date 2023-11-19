#pragma once

#include <random>
#include <type_traits>

template <typename T>
T get_rand_float(const T &lower_limit, const T &upper_limit)
{
    static_assert(std::is_floating_point_v<T>, "...");

    std::random_device seed_generator{};
    std::mt19937_64 random_generator{seed_generator()};
    std::uniform_int_distribution<int> random_distribution{
        static_cast<int>(lower_limit),
        static_cast<int>(upper_limit)};

    return static_cast<T>(random_distribution(random_generator));
}

class AirConditioner
{
public:
    AirConditioner() = default;
    AirConditioner(const float _target_temp_cel)
        : target_temp_cel(_target_temp_cel)
    {
        std::cout << "The AC has a target temp of " << target_temp_cel << '\n';
    };
    ~AirConditioner() = default;

    float measure() const;
    int activate(const float current_temp_cel);

private:
    bool heat(const int duration_min);
    bool cool(const int duration_min);

    float curr_temp_cel;
    float target_temp_cel = 20.0F;
};
