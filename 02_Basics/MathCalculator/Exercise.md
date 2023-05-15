# Exercise

In this exercise, you have to use the datatypes **double** and **int** for certain computations.

Implement the following functions:

```cpp
double calculate_pi(std::uint32_t num_iterations);

void print_dec_to_bin(std::uint8_t value);
```

## Calculate Pi

With the following formula, you can compute $\frac{\pi}{4}$.  
Implement the formula in the function with $n$ = **num_iterations**.  
Use a for-loop to sum up the values.

$x = \frac{\pi}{4} = \sum_0^n \frac{1}{(4n + 1)} - \frac{1}{(4n + 3)}$

At the end multiply by 4 before you return the value.  
So the returned value will be an approximation of $\pi$ and not $\frac{\pi}{4}$.

## Decimal to Binary

Implement a function that prints out the binary representation of the positive decimal input.

E.g. the decimal number 142 would be 10001110 in binary.

If you do not know how the binary system works, refer to the Wikipedia [link](https://en.wikipedia.org/wiki/Binary_number). Since this knowledge is not only important for this exercise but in general for a programmer.

### Hint

To compute $2^i$ you can use:

```cpp
#include <cmath>

std::pow(2, i)
```

## Main Function

```cpp
int main()
{
    std::uint32_t num_iterations = 1'000'000;
    double pi = 3.14159265358979323846;
    double pi_calculated = calculate_pi(num_iterations);

    std::cout << std::setprecision(30);
    std::cout << "pi (calculated): " << pi_calculated << '\n';
    std::cout << "pi (correct): " << pi << '\n';

    std::uint8_t dec = 0b10001110;
    print_dec_to_bin(dec);

    test_cases(); // This should not fail!
}
```
