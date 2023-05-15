#include <vector>
#include <filesystem>

#include "lib.h"

bool is_source_file(const fs::path &file)
{
    const auto allowed_extensions =
        std::vector<std::string>{".cc", ".cxx", ".cpp"};

    for (const auto &extension : allowed_extensions)
    {
        if (file.extension() == extension)
        {
            return true;
        }
    }

    return false;
}

std::vector<fs::path> get_source_files_in_dir(const fs::path &dir)
{
    auto files = std::vector<fs::path>{};

    const auto end = fs::directory_iterator{};
    for (auto it = fs::directory_iterator(dir); it != end; ++it)
    {
        const auto current_file = *it;

        if (fs::is_regular_file(current_file.path()) &&
            is_source_file(current_file.path()))
        {
            files.push_back(current_file);
        }
    }

    return files;
}

void compile_file(fs::path source_file)
{
    const auto source_file_string = source_file.string();
    auto command = "g++ -c " + source_file_string;

    source_file.replace_extension("o");
    const auto object_file_string = source_file.string();
    command += " -o " + object_file_string;

    std::system(command.c_str());
}

fs::path link_files(FileVec source_files)
{
    auto command = std::string{"g++ "};

    for (auto &source_file : source_files)
    {
        source_file.replace_extension("o");
        const auto object_file_string = source_file.string();

        command += object_file_string + " ";
    }

    auto executable_path = source_files[0].parent_path();
    executable_path /= "test";

    command += " -o " + executable_path.string();
    std::system(command.c_str());

    return executable_path;
}

void run(const fs::path &executable_path)
{
    const auto executable_path_string = executable_path.string();

    std::system(executable_path_string.c_str());
}
