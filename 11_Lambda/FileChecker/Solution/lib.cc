#include <algorithm>
#include <array>
#include <filesystem>
#include <vector>

#include "lib.h"

namespace fs = std::filesystem;

bool number_of_source_files(const FileVec &files)
{
    return std::count_if(files.begin(), files.end(), [](const auto &file) {
        return (is_c_source_file(file) || is_cpp_source_file(file));
    });
}

bool number_of_header_files(const FileVec &files)
{
    return std::count_if(files.begin(), files.end(), [](const auto &file) {
        return (is_c_header_file(file) || is_cpp_header_file(file));
    });
}

bool is_c_source_file(const fs::path &file)
{
    const auto allowed_extension = std::array<std::string, 1>{".c"};

    return file_extension_check(allowed_extension, file);
}

bool is_cpp_source_file(const fs::path &file)
{
    const auto allowed_extension =
        std::array<std::string, 3>{".cc", ".cpp", ".cxx"};

    return file_extension_check(allowed_extension, file);
}

bool is_c_header_file(const fs::path &file)
{
    const auto allowed_extension = std::array<std::string, 1>{".h"};

    return file_extension_check(allowed_extension, file);
}

bool is_cpp_header_file(const fs::path &file)
{
    const auto allowed_extension =
        std::array<std::string, 4>{".h", ".hh", ".hxx", ".hpp"};

    return file_extension_check(allowed_extension, file);
}
