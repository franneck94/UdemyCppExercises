#include <filesystem>
#include <map>
#include <string>
#include <string_view>
#include <vector>

#include "Lib.h"

void clean_text(std::string &text)
{
    replace_all(text, ".", "");
    replace_all(text, ",", "");
    replace_all(text, "!", "");
    replace_all(text, "?", "");
    replace_all(text, "\n", "");
    replace_all(text, "\t", "");
}

void replace_all(std::string &text,
                 std::string_view what,
                 std::string_view with)
{
    for (std::size_t pos = 0; pos != std::string::npos; pos += with.length())
    {
        pos = text.find(what.data(), pos, what.length());

        if (pos != std::string::npos)
        {
            text.replace(pos, what.length(), with.data(), with.length());
        }
    }
}

WordVector split_text(const std::string &text, char delimiter)
{
    auto words = WordVector{};

    auto iss = std::istringstream{text};
    auto item = std::string{};

    while (std::getline(iss, item, delimiter))
    {
        words.push_back(item);
    }

    return words;
}

CountedWordsMap count_words(const WordVector &words)
{

}

WordCountVec map_to_vector(const CountedWordsMap &counted_words)
{

}

void sort_word_counts(WordCountVec &word_counts)
{
}
