# Exercise

Implement the functions from chapter 7 as template functions:

```cpp
bool equal(Iterator first1, Iterator last1, Iterator first2);

Iterator fill_n(Iterator first, std::size_t count, const std::int32_t &value);

void iota(Iterator first, Iterator last, std::int32_t value);

Iterator copy(Iterator first, Iterator last, Iterator d_first);

std::int32_t accumulate(Iterator first, Iterator last, std::int32_t init);
```

## Main Function

```cpp
int main()
{
    auto vec1 = std::vector<std::uint32_t>(5, 0);
    auto vec2 = std::vector<std::uint32_t>(5, 0);

    std::cout << std::boolalpha << mystd::equal(vec1.begin(), vec1.end(), vec2.begin()) << std::dec << '\n';

    mystd::fill_n(vec1.begin(), 5, 1);
    print_vector(vec1);

    mystd::iota(vec2.begin(), vec2.end(), 0);
    print_vector(vec2);

    std::cout << std::boolalpha << mystd::equal(vec1.begin(), vec1.end(), vec2.begin()) << std::dec << '\n';

    mystd::copy(vec2.begin(), vec2.end(), vec1.begin());

    std::cout << std::boolalpha << mystd::equal(vec1.begin(), vec1.end(), vec2.begin()) << std::dec << '\n';

    const auto sum = mystd::accumulate(vec1.begin(), vec1.end(), 0);
    std::cout << sum << '\n';

    return 0;
}
```
