# Exercise

Implement the following functions:

```cpp
namespace fs = std::filesystem;

using FileVec = std::vector<fs::path>;

FileVec get_source_files_in_dir(const fs::path &dir);

bool is_source_file(const fs::path &file);

void compile_file(fs::path source_file);

fs::path link_files(FileVec source_files);

void run(const fs::path &executable_path);
```

- get_source_files_in_dir
  - Return a vector that stores all C++ source files in a folder
- is_source_file
  - Checks if a file is a C++ source file
- compile_file
  - Compile a single C++ source file
- link_files
  - Link all compiled object files into an executable
- run
  - Run the executable

Important compiler commands:

```bash
g++ -c Main.cc -o Main.o
g++ Main.o -o Main
Run on Windows: Main.exe
Run on Unix: ./Main
```

To run terminal commands from C++ program: **std::system()**

## Main Function

```cpp
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
```
