#pragma once

#include <string>
#include <string_view>
#include <vector>

void clean_text(std::string &text);

void replace_all(std::string &text,
                 std::string_view what,
                 std::string_view with);

template <typename T>
void split_text(const std::string &text, char delimiter, T result);

std::vector<std::string> split_text(const std::string &text, char delimiter);
