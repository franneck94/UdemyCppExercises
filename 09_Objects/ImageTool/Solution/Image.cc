#include <cmath>
#include <cstdlib>
#include <cstring>
#include <iostream>

#include "Image.hpp"
#include "distance.hpp"


Image::Image(const std::uint32_t width, const std::uint32_t height)
    : m_width(width), m_height(height),
      m_matrix(GrayscaleImage(m_width, std::vector<std::uint8_t>(m_height, 0)))
{
}

std::uint32_t Image::get_width() const
{
    return m_width;
}

std::uint32_t Image::get_height() const
{
    return m_height;
}

void Image::clear_image()
{
    m_matrix.clear();
    m_height = 0;
    m_width = 0;
}

void Image::set_pixel(const std::uint32_t x,
                      const std::uint32_t y,
                      const std::uint8_t value)
{
    m_matrix[x][y] = value;
}

void Image::resize_image(const std::uint32_t new_width,
                         const std::uint32_t new_height)
{
    if (new_width != m_width)
    {
        m_matrix.resize(new_width);
        m_width = new_width;
    }

    if (new_height != m_height)
    {
        for (auto &col : m_matrix)
        {
            col.resize(new_height);
        }

        m_height = new_height;
    }
}

void Image::fill_image(const std::uint8_t value)
{
    for (auto &col : m_matrix)
    {
        std::fill(col.begin(), col.end(), value);
    }
}

void Image::draw_line(const std::uint32_t x1,
                      const std::uint32_t y1,
                      const std::uint32_t x2,
                      const std::uint32_t y2,
                      const std::uint8_t value)
{
    std::uint32_t length = 0;

    if ((x1 < m_width) && (x2 < m_width) && (y1 < m_height) &&
        (y2 < m_height) && ((x1 == x2) || (y1 == y2)))
    {
        if (x1 == x2)
        {
            if (y1 < y2)
            {
                length = y2 - y1;

                for (std::uint32_t i = 0; i != length; ++i)
                {
                    set_pixel(x1, y1 + i, value);
                }
            }
            else
            {
                length = y1 - y2;

                for (std::uint32_t i = 0; i != length; ++i)
                {
                    set_pixel(x1, y2 + i, value);
                }
            }
        }
        else if (y1 == y2)
        {
            if (x1 < x2)
            {
                length = x2 - x1;

                for (std::uint32_t i = 0; i != length; ++i)
                {
                    set_pixel(x1 + i, y1, value);
                }
            }
            else
            {
                length = x1 - x2;

                for (std::uint32_t i = 0; i != length; ++i)
                {
                    set_pixel(x2 + i, y1, value);
                }
            }
        }
    }
}

void Image::draw_rectangle(const Rectangle &rectangle, const std::uint8_t value)
{
    draw_line(rectangle.x1, rectangle.y1, rectangle.x1, rectangle.y2, value);
    draw_line(rectangle.x2, rectangle.y1, rectangle.x2, rectangle.y2, value);
    draw_line(rectangle.x1, rectangle.y1, rectangle.x2, rectangle.y1, value);
    draw_line(rectangle.x1, rectangle.y2, rectangle.x2, rectangle.y2, value);
}

void Image::fill_rectangle(const Rectangle &rectangle, const std::uint8_t value)
{
    for (auto i = rectangle.x1; i < rectangle.x2; ++i)
    {
        for (auto j = rectangle.y1; j < rectangle.y2; ++j)
        {
            set_pixel(i, j, value);
        }
    }
}

void Image::draw_circle(const Circle &circle, const std::uint8_t value)
{
    const auto x_lower_bound = circle.x_midpoint - circle.radius;
    const auto x_upper_bound = circle.x_midpoint + circle.radius;
    const auto y_lower_bound = circle.y_midpoint - circle.radius;
    const auto y_upper_bound = circle.y_midpoint + circle.radius;

    for (auto i = x_lower_bound; i < x_upper_bound; i++)
    {
        for (auto j = y_lower_bound; j < y_upper_bound; j++)
        {
            const auto distance =
                get_distance(i, j, circle.x_midpoint, circle.y_midpoint);

            if (std::ceil(distance) == circle.radius)
            {
                set_pixel(i, j, value);
            }
        }
    }
}

void Image::fill_circle(const Circle &circle, const std::uint8_t value)
{
    const auto x_lower_bound = circle.x_midpoint - circle.radius;
    const auto x_upper_bound = circle.x_midpoint + circle.radius;
    const auto y_lower_bound = circle.y_midpoint - circle.radius;
    const auto y_upper_bound = circle.y_midpoint + circle.radius;

    for (auto i = x_lower_bound; i < x_upper_bound; i++)
    {
        for (auto j = y_lower_bound; j < y_upper_bound; j++)
        {
            const auto distance =
                get_distance(i, j, circle.x_midpoint, circle.y_midpoint);

            if (std::ceil(distance) <= circle.radius)
            {
                set_pixel(i, j, value);
            }
        }
    }
}

void Image::save_image(std::string_view file_name) const
{
    FILE *f = nullptr;

    const auto num_bytes = 3 * m_width * m_height;
    auto *img = new std::uint8_t[num_bytes]{};

    const auto filesize = 54 + 3 * m_width * m_height;

    for (std::uint32_t x = 0; x < m_width; ++x)
    {
        for (std::uint32_t y = 0; y < m_height; y++)
        {
            img[(x + y * m_width) * 3 + 2] = m_matrix[x][y] % 256;
            img[(x + y * m_width) * 3 + 1] = m_matrix[x][y] % 256;
            img[(x + y * m_width) * 3 + 0] = m_matrix[x][y] % 256;
        }
    }

    std::uint8_t
        bmpfileheader[14]{'B', 'M', 0, 0, 0, 0, 0, 0, 0, 0, 54, 0, 0, 0};
    std::uint8_t
        bmpinfoheader[40]{40, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 24, 0};
    std::uint8_t bmppad[3]{0, 0, 0};

    bmpfileheader[2] = static_cast<std::uint8_t>(filesize);
    bmpfileheader[3] = static_cast<std::uint8_t>(filesize >> 8);
    bmpfileheader[4] = static_cast<std::uint8_t>(filesize >> 16);
    bmpfileheader[5] = static_cast<std::uint8_t>(filesize >> 24);

    bmpinfoheader[4] = static_cast<std::uint8_t>(m_width);
    bmpinfoheader[5] = static_cast<std::uint8_t>(m_width >> 8);
    bmpinfoheader[6] = static_cast<std::uint8_t>(m_width >> 16);
    bmpinfoheader[7] = static_cast<std::uint8_t>(m_width >> 24);
    bmpinfoheader[8] = static_cast<std::uint8_t>(m_height);
    bmpinfoheader[9] = static_cast<std::uint8_t>(m_height >> 8);
    bmpinfoheader[10] = static_cast<std::uint8_t>(m_height >> 16);
    bmpinfoheader[11] = static_cast<std::uint8_t>(m_height >> 24);

    f = fopen(file_name.data(), "wb");
    if (f == nullptr)
    {
        delete[] img;
        img = nullptr;

        return;
    }

    fwrite(bmpfileheader, 1, 14, f);
    fwrite(bmpinfoheader, 1, 40, f);

    for (std::uint32_t i = 0; i < m_height; i++)
    {
        fwrite(img + (m_width * (m_height - i - 1) * 3), 3, m_width, f);
        fwrite(bmppad, 1, (4 - (m_width * 3) % 4) % 4, f);
    }

    fclose(f);
    f = nullptr;

    delete[] img;
    img = nullptr;
}
