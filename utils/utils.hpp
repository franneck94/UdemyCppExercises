#ifndef UTILS_H
#define UTILS_H

#include <array>
#include <cmath>
#include <exception>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <limits>
#include <map>
#include <random>
#include <sstream>
#include <string_view>
#include <unordered_map>
#include <vector>

constexpr double pi = 3.14159265358979311600;

template <typename T>
void print_array(const T *array, const std::size_t length)
{
    for (std::size_t i = 0; i < length - 1; i++)
    {
        std::cout << array[i] << ", ";
    }

    std::cout << array[length - 1] << '\n';
}

template <typename T, std::size_t S>
void print_array(const std::array<T, S> array)
{
    for (std::size_t i = 0; i < array.size() - 1; i++)
    {
        std::cout << array[i] << ", ";
    }

    std::cout << array[array.size() - 1] << '\n';
}

template <typename T>
void print_vector(const std::vector<T> &vector)
{
    for (std::size_t i = 0; i < vector.size() - 1; i++)
    {
        std::cout << vector[i] << ", ";
    }

    std::cout << vector[vector.size() - 1] << '\n';
}

template <>
void print_vector(
    const std::vector<std::pair<std::string, std::size_t>> &vector)
{
    for (std::size_t i = 0; i < vector.size() - 1; i++)
    {
        std::cout << vector[i].first << ": " << vector[i].second << ", ";
    }

    std::cout << vector[vector.size() - 1].first << ": "
              << vector[vector.size() - 1].second << '\n';
}

template <typename T, typename U>
void print_map(const std::map<T, U> Map)
{
    for (const auto &[Key, value] : Map)
    {
        std::cout << Key << ": " << value << '\n';
    }
}

std::string readFile(std::string_view file_path)
{
    auto str = std::string{};
    auto text = std::string{};

    if (!std::filesystem::exists(file_path))
    {
        std::cerr << "File does not exist!\n";
        throw std::invalid_argument("File does not exist!");
    }

    auto iffile = std::ifstream{};
    iffile.open(file_path.data());

    if (iffile.is_open())
    {
        while (std::getline(iffile, str))
        {
            text += str + '\n';
        }
    }

    iffile.close();

    return text;
}


template <typename T>
void random_vector(std::vector<T> &vec)
{
    std::mt19937 random_generator(22);
    std::uniform_int_distribution<T> random_distribution(-10, 10);

    for (auto &val : vec)
    {
        val = random_distribution(random_generator);
    }
}

void clear_console()
{
#if defined _WIN32
    system("cls");
#elif defined(__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
    system("clear");
#elif defined(__APPLE__)
    system("clear");
#else
    system("clear");
#endif
}

template <typename T>
inline auto is_close(T a, T b)
{
    return std::fabs(a - b) < std::numeric_limits<T>::epsilon();
}

template <typename T>
auto ranges_are_same(const T *a, const T *b, const std::size_t len)
{
    for (std::size_t i = 0; i < len; i++)
    {
        if (a[i] != b[i])
            return false;
    }

    return true;
}

template <typename T>
auto vectors_are_same(const std::vector<T> &a, const std::vector<T> &b)
{
    if (a.size() != b.size())
        return false;

    for (std::size_t i = 0; i < a.size(); i++)
    {
        if (a[i] != b[i])
            return false;
    }

    return true;
}

#endif /* UTILS_H */
