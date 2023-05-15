#pragma once

#include <array>
#include <filesystem>
#include <string>
#include <vector>

namespace fs = std::filesystem;
using FileVec = std::vector<fs::path>;

bool is_c_source_file(const fs::path &file);

bool is_cpp_source_file(const fs::path &file);

bool is_c_header_file(const fs::path &file);

bool is_cpp_header_file(const fs::path &file);

bool number_of_source_files(const FileVec &files);

bool number_of_header_files(const FileVec &files);

template <std::size_t N>
bool file_extension_check(const std::array<std::string, N> &allowed_extension,
                          const fs::path &file)
{
}
