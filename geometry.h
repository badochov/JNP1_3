#ifndef JNP1_3_GEOMETRY_H
#define JNP1_3_GEOMETRY_H

#include <initializer_list>
#include <cstddef>
#include <vector>
#include <cstdint>

class Position;

class Vector {
public:
    Vector(int_fast32_t x, int_fast32_t y);

    explicit Vector(Position point);

    int_fast32_t x() const;

    int_fast32_t y() const;

    Vector reflection() const;

    bool operator==(const Vector &other) const;

    Vector &operator+=(const Vector &other);

private:
    int_fast32_t _x;
    int_fast32_t _y;
};

class Position {
public:
    Position(int_fast32_t x, int_fast32_t y);

    explicit Position(Vector vec);

    int_fast32_t x() const;

    int_fast32_t y() const;

    Position reflection() const;

    bool operator==(const Position &other) const;

    Position &operator+=(const Vector &vec);

    static const Position &origin();

private:
    Vector _vec;
};

class Rectangle {
public:
    Rectangle(int_fast32_t width, int32_t height);

    Rectangle(int_fast32_t width, int32_t height, Position pos);

    Rectangle(const Rectangle &) = default;

    Rectangle(Rectangle &&) = default;

    bool operator==(const Rectangle &rect) const;

    const Position &pos() const;

    int_fast32_t width() const;

    int_fast32_t height() const;

    Rectangle reflection() const;

    Rectangle &operator+=(const Vector &vec);

    Rectangle &operator=(Rectangle &&r) = default;

    int_fast64_t area() const;

private:
    Position _left_bottom_corner;
    int_fast32_t _width;
    int_fast32_t _height;
};

class Rectangles {
public:
    Rectangles() = default;

    Rectangles(const Rectangles &) = default;

    Rectangles(std::initializer_list<Rectangle>);

    Rectangle &operator[](size_t i);

    const Rectangle &operator[](size_t i) const;

    bool operator==(const Rectangles &rectangles);

    Rectangles &operator+=(const Vector &vec);

    size_t size() const;

    Rectangles &operator=(Rectangles &&rhs) noexcept;

private:
    std::vector<Rectangle> _rects;
};

Rectangle merge_horizontally(const Rectangle &rect1, const Rectangle &rect2);

Rectangle merge_vertically(const Rectangle &rect1, const Rectangle &rect2);

Rectangle merge_all(const Rectangles &rectangles);

Rectangles &operator+(const Rectangles &rects, const Vector &vec);

Rectangles &operator+(const Vector &vec, const Rectangles &rects);

Rectangle &operator+(const Rectangle &rect, const Vector &vec);

Rectangle &operator+(const Vector &vec, const Rectangle &rect);


Rectangles &operator+(Rectangles &&rects, const Vector &vec);

Rectangles &operator+(const Vector &vec, Rectangles &&rects);

Rectangle &operator+(Rectangle &&rect, const Vector &vec);

Rectangle &operator+(const Vector &vec, Rectangle &&rect);

Vector &operator+(const Vector &vec1, const Vector &vec2);

Position &operator+(const Position &point, const Vector &vec);

Position &operator+(const Vector &vec, const Position &point);

#endif //JNP1_3_GEOMETRY_H
