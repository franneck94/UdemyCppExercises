#pragma once

#include <vector>
#include <filesystem>

namespace fs = std::filesystem;
using FileVec = std::vector<fs::path>;

FileVec get_source_files_in_dir(const fs::path &dir);

bool is_source_file(const fs::path &file);

void compile_file(fs::path source_file);

fs::path link_files(FileVec source_files);

void run(const fs::path &executable_path);
