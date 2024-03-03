# Exercise

Implement the following functions:

```cpp
using It = std::vector<std::int32_t>::iterator;

using DifferenceType = It::difference_type;

void advance(It &it, DifferenceType n);

DifferenceType distance(It first, It last);

It next(It it, DifferenceType n = 1);

It prev(It it, DifferenceType n = 1);
```

- advance
  - Step n-steps to the right (forward) with the iterator if n is positive
  - Step n-steps to the left (backward) with the iterator if n is negative
- distance
  - Compute the distance between two iterators of the same container
- next
  - Step 1-step to the right (forward) with the iterator
  - Note: 1-step is the default value for the parameter n
- prev
  - Step 1-step to the left (backward) with the iterator
  - Note: 1-step is the default value for the parameter n

The functions should work for vectors, lists etc.

## Main Function

```cpp
int main()
{
    auto vec = std::vector<int>{1, 2, 3};
    auto vec_it = vec.begin();

    const auto next_it = mystd::next(vec_it);
    std::cout << "*next_it: " << *next_it << '\n';

    const auto prev_it = mystd::prev(next_it);
    std::cout << "*prev_it: " << *prev_it << '\n';

    mystd::advance(vec_it, 2);
    std::cout << "advance: " << *vec_it << '\n';

    const auto dist = mystd::distance(vec_it, vec.end());
    std::cout << "distance: " << dist << '\n';

    return 0;
}
```
