# Exercise

Implement the following functions:

```cpp
using WordCountPair = std::pair<std::string, std::size_t>;

void clean_text(std::string &text);

void replace_all(std::string &text, std::string_view what, std::string_view with);

std::vector<std::string> split_text(const std::string &text, char delimiter);
```

Read in the text of the local **text.txt** file, the **readFile** is defined in the **utils** header:

```cpp
#include "utils.hpp"

auto text = readFile("C:/Users/Jan/OneDrive/_Coding/Udemy_CppExt/5_String/SplitWords/text.txt");
```

- clean_text
  - Replace the following characters with nothing: ['.', ',', '!', '?', '\n', '\t']
- replace_all
  - Iterate over the string and replace all **what** entries with **with**
- split_text
  - Split the text on every word => One entry in the resulting vector is one word

E.g. "Dolor sit vero" => ["Dolor", "sit", "vero"]

## Main Function

```cpp
int main()
{
    auto text =
        readFile("C:/Users/Jan/OneDrive/_Coding/udemy_cppExt/6_Container/word_count/text.txt");
    std::cout << text << '\n' << '\n';

    cleanText(text);
    std::cout << text << '\n' << '\n';

    const auto splittedText = splitText(text, ' ');
    print_vector(splittedText);

    return 0;
}
```
