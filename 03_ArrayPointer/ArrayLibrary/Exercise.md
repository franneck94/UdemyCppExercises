# Exercise

Implement the following functions:

```cpp
void remove_duplicates(std::int32_t *array, std::size_t &length);

void rotate_left(std::int32_t *array, std::size_t length);

void rotate_right(std::int32_t *array, std::size_t length);
```

- Remove Duplicates
  - Remove all duplicates in the array
  - By Remove I mean
    - move  the element to the end of the array and decrease the length of the array by one, hence the value is not used anymore
- Rotate Left
  - Rotate all elements of the array to the left
  - Rotate Left: [1, 2, 3] => [2, 3, 1]  
- Rotate Right
  - Rotate all elements of the array to the right
  - Rotate Right: [1, 2, 3] => [3, 1, 2]  

Note: Make sure that the input pointers are valid!

Note: Assume that a number can be at most 2 times in the array!

## Main Function

```cpp
int main()
{
    std::size_t length = 6;
    std::int32_t array[]{1, 1, 2, 3, 3, 4};

    remove_duplicates(array, length);
    print_array(array, length);

    rotate_left(array, length);
    print_array(array, length);

    rotate_right(array, length);
    print_array(array, length);

    test_cases(); // This should not fail

    return 0;
}
```
