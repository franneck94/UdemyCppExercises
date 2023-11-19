# Exercise

Copy your Shape classes from the last exercise into this folder.

Extend the following class.

```cpp
class Image
{
public:
    ...

    void draw_rectangle(const Rectangle &rectangle, const std::uint8_t value);

    void fill_rectangle(const Rectangle &rectangle, const std::uint8_t value);

    void draw_circle(const Circle &circle, const std::uint8_t value);

    void fill_circle(const Circle &circle, const std::uint8_t value);

    ...
};

```

Here we extend the Image class from the main course.
We will add the following functions:

- draw_rectangle: Draw (only) the border of a rectangle with the color **value**
- fill_rectangle:  Draw the border of a rectangle with the color **value** and also fill all pixels inside the rectangle with the color
- draw_circle: Draw (only) the border of a circle with the color **value**
- fill_circle: Draw the border of a circle with the color **value** and also fill all pixels inside the circle with the color

## Main Function

```cpp
int main()
{
    auto circle1 = Circle{200, 200, 20};
    auto circle2 = Circle{250, 250, 20};

    auto rectangle1 = Rectangle{100, 100, 150, 150};
    auto rectangle2 = Rectangle{300, 300, 350, 350};

    std::cout << "Distance c1-c2: " << circle1.midpoint_distance(&circle2) << '\n';
    std::cout << "Distance c1-r1: " << circle1.midpoint_distance(&rectangle1) << '\n';
    std::cout << "Distance r1-r2: " << rectangle1.midpoint_distance(&rectangle2) << '\n';
    std::cout << "Distance r1-x2: " << rectangle1.midpoint_distance(&circle2) << '\n';

    Image image1(400, 400);
    image1.fill_image(125);

    image1.draw_rectangle(rectangle1, 255);
    image1.draw_circle(circle1, 255);
    image1.fill_rectangle(rectangle2, 255);
    image1.fill_circle(circle2, 255);
    image1.save_image("image.bmp");

    return 0;
}

```
