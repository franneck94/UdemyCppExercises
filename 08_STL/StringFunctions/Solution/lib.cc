#include <algorithm>

#include "lib.h"

namespace mystd
{

bool is_palindrom(std::string_view str)
{
    return std::equal(str.begin(), str.end(), str.rbegin());
}

bool starts_with(std::string_view str, std::string_view substr)
{
    return std::equal(substr.begin(), substr.end(), str.begin());
}

bool ends_with(std::string_view str, std::string_view substr)
{
    return std::equal(substr.rbegin(), substr.rend(), str.rbegin());
}

bool contains(std::string_view str, std::string_view substr)
{
    const auto substr_length = substr.length();

    for (auto it = str.begin(); it < str.end() - substr_length + 1;)
    {
        const auto found = std::equal(substr.begin(), substr.end(), it);

        if (found == true)
        {
            return true;
        }

        ++it;
    }

    return false;
}

std::size_t num_occurences(std::string_view str, std::string_view substr)
{
    auto result = std::size_t{0};
    const auto substr_length = substr.length();

    for (auto it = str.begin(); it < str.end() - substr_length + 1;)
    {
        auto found = std::equal(substr.begin(), substr.end(), it);

        if (found == true)
        {
            ++result;
        }

        ++it;
    }

    return result;
}

} // namespace mystd
