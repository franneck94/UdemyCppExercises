#include <iostream>

#include "Shape.hpp"

int main()
{
    auto circle1 = Circle{200, 200, 20};
    auto circle2 = Circle{250, 250, 20};

    auto rectangle1 = Rectangle{100, 100, 150, 150};
    auto rectangle2 = Rectangle{300, 300, 350, 350};

    std::cout << "Distance c1-c2: " << circle1.midpoint_distance(&circle2)
              << '\n';
    std::cout << "Distance c1-r1: " << circle1.midpoint_distance(&rectangle1)
              << '\n';
    std::cout << "Distance r1-r2: " << rectangle1.midpoint_distance(&rectangle2)
              << '\n';
    std::cout << "Distance r1-x2: " << rectangle1.midpoint_distance(&circle2)
              << '\n';

    return 0;
}
