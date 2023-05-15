#pragma once

#include <filesystem>
#include <map>
#include <string>
#include <string_view>
#include <vector>

namespace fs = std::filesystem;

using WordVector = std::vector<std::string>;
using WordCountPair = std::pair<std::string, std::size_t>;
using WordCountVec = std::vector<WordCountPair>;
using CountedWordsMap = std::map<std::string, std::size_t>;

void clean_text(std::string &text);

void replace_all(std::string &text,
                 std::string_view what,
                 std::string_view with);

WordVector split_text(const std::string &text, char delimiter);

CountedWordsMap count_words(const WordVector &words);

WordCountVec map_to_vector(const CountedWordsMap &counted_words);

void sort_word_counts(WordCountVec &word_counts);
