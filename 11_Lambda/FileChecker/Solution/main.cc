#include <filesystem>
#include <iostream>
#include <string>
#include <vector>

#include "lib.h"
#include "utils.hpp" // dont forget the include setting for the c++ runner

namespace fs = std::filesystem;

int main(int argc, char **argv)
{
    auto dir = fs::path{};

    if (argc != 2)
    {
        dir /= fs::current_path();
        dir /= "test";
    }
    else
    {
        const auto input_path = std::string(argv[1]);
        dir = fs::path(input_path);
    }

    auto all_files = FileVec{};
    for (auto it = fs::directory_iterator(dir); it != fs::directory_iterator{};
         ++it)
    {
        all_files.push_back(*it);
    }

    const auto number_sources = number_of_source_files(all_files);
    const auto number_headers = number_of_header_files(all_files);

    std::cout << number_sources << '\n';
    std::cout << number_headers << '\n';

    for (const auto &file : all_files)
    {
        std::cout << "File: " << file << '\n';
        std::cout << std::boolalpha;
        std::cout << "c_header_file: " << is_c_header_file(file) << '\n';
        std::cout << "c_source_file: " << is_c_source_file(file) << '\n';
        std::cout << "cpp_header_file: " << is_cpp_header_file(file) << '\n';
        std::cout << "cpp_source_file: " << is_cpp_source_file(file) << '\n';
    }
}
