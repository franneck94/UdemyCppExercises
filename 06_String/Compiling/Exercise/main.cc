#include <algorithm>
#include <filesystem>
#include <iostream>
#include <string>
#include <vector>

#include "utils.hpp"
#include "lib.h"

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

    auto files = get_source_files_in_dir(dir);

    print_vector(files);

    for (const auto &file : files)
    {
        compile_file(file);
    }

    const auto executable_path = link_files(files);

    run(executable_path);
}
