#include <iostream>

#include "Image.hpp"
#include "Shape.hpp"

int main()
{
    auto circle1 = Circle{200, 200, 20};
    auto circle2 = Circle{250, 250, 20};

    auto rectangle1 = Rectangle{100, 100, 150, 150};
    auto rectangle2 = Rectangle{300, 300, 350, 350};

    Image image1(400, 400);
    image1.fill_image(125);

    image1.draw_rectangle(rectangle1, 255);
    image1.draw_circle(circle1, 255);
    image1.fill_rectangle(rectangle2, 255);
    image1.fill_circle(circle2, 255);
    image1.save_image("image.bmp");

    return 0;
}
