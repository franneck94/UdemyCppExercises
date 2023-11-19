# Exercise

Implement the following unit conversions and math operations with templated functions in the *Units.hpp* header file:

- PI
  - Add a tamplate variable for PI
  - Such that the user can create a float ,double or long double based on the template
  - You can take this value: 3.14159265358979323846
- ms_to_s
  - Milliseconds to seconds
  - Add a static assert to check:
    - The Input (ms) must be an integral type
    - The output (s) must he a floating type
- deg_to_rad
  - Degrees ($\alpha$) to radians ($\theta$)
  - $\theta = \alpha * \frac{\pi}{180}$
  - Add a static assert to check:
    - The Input and Output must be a floating type
- kph_to_mps
  - $\frac{km}{hour}$ to $\frac{m}{sec}$
  - Add a static assert to check:
    - The Input and Output must be a floating type
- mps_to_kph
  - $\frac{m}{sec}$ to $\frac{km}{hour}$
  - Add a static assert to check:
    - The Input and Output must be a floating type

## Bonus Exercise

- rotate_point
  - Rotates a 2D point $p = \begin{pmatrix}x\\y\end{pmatrix}$ based on a given rotation value $\theta$ (in radians)
  - $M = \begin{pmatrix}cos(\theta) & -sin(\theta)\\sin(\theta) & cos(\theta)\end{pmatrix}$
  - To rotate compute: $p' = Mp$
  - The function should return a pair (the rotated x and y value)
  - Add a static assert to check:
    - The Input and Output must be a floating type

```cpp
  ... rotate_point(const T theta, const T x, const T y)
```

For more info see [here](https://en.wikipedia.org/wiki/Rotations_and_reflections_in_two_dimensions)

### Note

All functions should be constexpr.  
You can add the *[[nodiscard]]* attributes tag (see [here](https://en.cppreference.com/w/cpp/language/attributes/nodiscard)).

## Main Function

```cpp
int main()
{
    const float x = 5.0F;
    const float y = 4.0F;

    const auto deg = 10.0F;
    const auto rad = deg_to_rad(deg);

    const auto [x_, y_] = rotate_point(rad, x, y);
    std::cout << x_ << " " << y_ << std::endl;

    return 0;
}
```
