# Exercise

In this exercise, you have to use an **int** datatype for certain computations.

Implement the following functions:

```cpp
std::uint32_t modulo(std::uint32_t number_a, std::uint32_t number_b);

std::uint32_t sum_of_digits(std::uint32_t number);

std::uint32_t cross_sum(std::uint32_t number);
```

- Modulo
  - Implement the modulo operator (a % b = c)
  - E.g. 10 % 4 = 2, 10 % 3 = 1, 10 % 2 = 0
- Sum Of Digits
  - Number of decimal digits
  - E.g. 128 = 3 Digits
- Cross Sum (*Quersumme*)
  - Add up all decimal digits
  - E.g. 123 = 6, 1234 = 10

Note:

The datatype std::uint32_t is defined in the **cstdint** header file.

```cpp
#include <cstdint>

std::uint32_t i = 0;
```

These datatypes ensure that for every operating system and compiler the value range is the same (for exactly this type 32 bit).

## Main Function

```cpp
int main()
{
    std::uint32_t input_number = 0;

    std::cout << "Please enter a unsinged integer: ";
    std::cin >> input_number;

    std::cout << input_number << " % 3: " << modulo(input_number, 3) << '\n';
    std::cout << "sum_of_digits: " << sum_of_digits(input_number) << '\n';
    std::cout << "cross_sum: " << cross_sum(input_number) << '\n';

    test_cases();
}
```
