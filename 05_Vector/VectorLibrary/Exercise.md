# Exercise

Implement the following functions:

```cpp
void remove_duplicates(std::vector<std::int32_t> &vector);

void rotate_left(std::vector<std::int32_t> &vector);

void rotate_right(std::vector<std::int32_t> &vector);

void swap_boundaryValues(std::vector<std::int32_t> &vector);
```

Adapt the functions from Chapter 2 such that you use vectors as an input.

- Swap Boundary Values: Swap the first and the last value of the array

E.g. [1, 2, 3, 4] => [4, 2, 3, 1]

## Main Function

```cpp
int main()
{
    auto vector = std::vector<std::int32_t>{1, 1, 2, 3, 3, 4};

    std::cout << "remove_duplicates: " << '\n';
    remove_duplicates(vector);
    print_vector(vector);

    std::cout << "rotate_left: " << '\n';
    rotate_left(vector);
    print_vector(vector);

    std::cout << "rotate_right: " << '\n';
    rotate_right(vector);
    print_vector(vector);

    test_cases();

    return 0;
}
```
