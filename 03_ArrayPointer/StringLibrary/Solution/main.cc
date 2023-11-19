#include <cassert>
#include <iostream>
#include <string>

#include "lib.h"

void test_cases();

int main()
{
    char in_text[50]{};
    char compare_text1[50]{"jan"};
    char compare_text2[50]{"ja"};

    std::cout << "Please enter any text: ";
    std::cin >> in_text;

    std::cout << "to_upper_case: " << to_upper_case(in_text) << '\n';
    std::cout << "to_lower_case: " << to_lower_case(in_text) << '\n';
    std::cout << "string_length: " << string_length(in_text) << '\n';
    std::cout << std::boolalpha;
    std::cout << "jan == jan: " << string_equal(in_text, compare_text1) << '\n';
    std::cout << "jan == ja: " << string_equal(in_text, compare_text2) << '\n';

    test_cases(); // This should not fail

    return 0;
}

void test_cases()
{
    char in_text[] = "JaNa";
    assert(std::string{to_upper_case(in_text)} == std::string{"JANA"});
    assert(std::string{to_lower_case(in_text)} == std::string{"jana"});
    assert(string_length(in_text) == 4U);
    assert(string_length(in_text) == std::string{in_text}.size());
    assert(string_equal(to_upper_case(in_text), "JANA"));
    assert(string_equal(to_lower_case(in_text), "jana"));
}
