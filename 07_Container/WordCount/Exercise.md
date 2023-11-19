# Exercise

Implement the following functions:

```cpp
namespace fs = std::filesystem;

using WordVector = std::vector<std::string>;
using WordCountPair = std::pair<std::string, std::size_t>;
using WordCountVec = std::vector<WordCountPair>;
using counted_wordsMap = std::map<std::string, std::size_t>;

void clean_text(std::string &text);

void replace_all(std::string &text, std::string_view what, std::string_view with);

WordVector split_text(const std::string &text, char delimiter);

CountedWordsMap count_words(const WordVector &words);

WordCountVec map_to_vector(const CountedWordsMap &counted_words);

void sort_word_counts(WordCountVec &word_counts);
```

- count_words:
  - count the different words from the word vector and store the word, occurence pairs to the map
  - E.g. {"jan", "is", "my", "name"} {{"Jan": 1, "is": 1, "my": 1, "name": 1}}
- map_to_vector
  - store the word count map to the word count vector (needed for sorting)
- sort_word_counts
  - Sort the word count vector by the counts

## Main Function

```cpp
int main()
{
    auto current_path = fs::current_path();
    current_path /= "text.txt";

    auto text = readFile(current_path.string());
    std::cout << text << '\n' << '\n';

    clean_text(text);
    std::cout << text << '\n' << '\n';

    auto splitted_text = split_text(text, ' ');
    print_vector(splitted_text);

    auto counted_words = count_words(splitted_text);
    print_map(counted_words);

    auto countedwords_vector = mapto_vector(counted_words);

    sortword_counts(countedwords_vector);
    print_vector(countedwords_vector);

    return 0;
}
```
