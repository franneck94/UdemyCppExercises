#include <iostream>
#include <sstream>
#include <string>
#include <string_view>
#include <vector>

#include "Lib.h"
#include "utils.hpp" // dont forget the include setting for the c++ runner

int main()
{
    auto text = readFile("C:/Users/Jan/OneDrive/_Coding/UdemyCppExercises/"
                         "06_String/SplitWords/Solution/text.txt");
    std::cout << text << '\n' << '\n';

    clean_text(text);
    std::cout << text << '\n' << '\n';

    const auto splittedText = split_text(text, ' ');
    print_vector(splittedText);

    return 0;
}
