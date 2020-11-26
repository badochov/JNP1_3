#ifndef JNP1_3_GEOMETRY_H
#define JNP1_3_GEOMETRY_H

#include <initializer_list>
#include <vector>
#include <cstdint>

class Position;

class Vector {
public:
    using coordinate_t = int_fast32_t;

    Vector(coordinate_t x, coordinate_t y);

    Vector(const Vector &other) = default;

    Vector &operator=(const Vector &other) = default;

    explicit Vector(const Position &point);

    [[nodiscard]] coordinate_t x() const;

    [[nodiscard]] coordinate_t y() const;

    [[nodiscard]] Vector reflection() const;

    bool operator==(const Vector &other) const;

    Vector &operator+=(const Vector &other);

private:
    coordinate_t _x;
    coordinate_t _y;
};


class Position {
public:
    Position(Vector::coordinate_t x, Vector::coordinate_t y);

    Position(const Position &other) = default;

    Position &operator=(const Position &other) = default;

    explicit Position(const Vector &vec);

    [[nodiscard]] Vector::coordinate_t x() const;

    [[nodiscard]] Vector::coordinate_t y() const;

    [[nodiscard]] Position reflection() const;

    bool operator==(const Position &other) const;

    Position &operator+=(const Vector &vec);

    static const Position &origin();

private:
    Vector _vec;
};


class Rectangle {
public:
    using area_t = uint_fast32_t;

    using dimension_t = int_fast32_t;

    Rectangle(dimension_t width, dimension_t height, const Position &pos = Position::origin());

    Rectangle(const Rectangle &other) = default;

    Rectangle &operator=(const Rectangle &other) = default;

    bool operator==(const Rectangle &rect) const;

    [[nodiscard]] const Position &pos() const;

    [[nodiscard]] dimension_t width() const;

    [[nodiscard]] dimension_t height() const;

    [[nodiscard]] Rectangle reflection() const;

    Rectangle &operator+=(const Vector &vec);

    [[nodiscard]] area_t area() const;

private:
    Vector::coordinate_t _width;
    Vector::coordinate_t _height;
    Position _left_bottom_corner;
};


class Rectangles {
public:
    using size_t = std::vector<Rectangle>::size_type;

    Rectangles() = default;

    Rectangles(std::initializer_list<Rectangle>);

    Rectangles(const Rectangles &other) = default;

    Rectangles &operator=(const Rectangles &other) = default;

    Rectangles(Rectangles &&other) = default;

    Rectangles &operator=(Rectangles &&other) = default;

    Rectangle &operator[](size_t i);

    const Rectangle &operator[](size_t i) const;

    bool operator==(const Rectangles &rectangles);

    Rectangles &operator+=(const Vector &vec);

    [[nodiscard]] Rectangles::size_t size() const;

private:
    std::vector<Rectangle> _rects;
};


Rectangle merge_horizontally(const Rectangle &rect1, const Rectangle &rect2);

Rectangle merge_vertically(const Rectangle &rect1, const Rectangle &rect2);

Rectangle merge_all(const Rectangles &rectangles);


Rectangles operator+(Rectangles &&rects, const Vector &vec);

Rectangles operator+(const Vector &vec, Rectangles &&rects);

Rectangles operator+(const Rectangles &rects, const Vector &vec);

Rectangles operator+(const Vector &vec, const Rectangles &rects);

Rectangle operator+(Rectangle rect, const Vector &vec);

Rectangle operator+(const Vector &vec, Rectangle rect);

Vector operator+(Vector vec1, const Vector &vec2);

Position operator+(Position point, const Vector &vec);

Position operator+(const Vector &vec, Position point);

#endif //JNP1_3_GEOMETRY_H
