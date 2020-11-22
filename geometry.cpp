#include "geometry.h"
#include <cassert>

namespace {
    inline bool can_be_merged_horizontally(const Rectangle &rect1, const Rectangle &rect2) {
        return rect1.width() == rect2.width()
               && rect1.pos().y() == rect2.pos().y()
               && rect1.pos().y() + rect1.height() == rect2.pos().y();
    }

    inline bool can_be_merged_vertically(const Rectangle &rect1, const Rectangle &rect2) {
        return rect1.height() == rect2.height()
               && rect1.pos().y() == rect2.pos().y()
               && rect1.pos().x() + rect1.width() == rect2.pos().x();
    }

    inline Rectangle merge_vertically_helper(const Rectangle &rect1, const Rectangle &rect2) {
        int_fast32_t new_width = rect1.width() + rect2.width();
        int_fast32_t new_height = rect1.height();
        return Rectangle(new_width, new_height, rect1.pos());
    }

    inline Rectangle merge_horizontally_helper(const Rectangle &rect1, const Rectangle &rect2) {
        int_fast32_t new_width = rect1.width();
        int_fast32_t new_height = rect1.height() + rect2.height();
        return Rectangle(new_width, new_height, rect1.pos());
    }
}


Rectangle merge_vertically(const Rectangle &rect1, const Rectangle &rect2) {
    assert(can_be_merged_vertically(rect1, rect2));
    return merge_vertically_helper(rect1, rect2);
}

Rectangle merge_horizontally(const Rectangle &rect1, const Rectangle &rect2) {
    assert(can_be_merged_horizontally(rect1, rect2));
    return merge_horizontally_helper(rect1, rect2);

}

Rectangle merge_all(const Rectangles &rectangles) {
    assert(rectangles.size());
    Rectangle rect = rectangles[0];
    for (size_t i = 1; i < rectangles.size(); ++i) {
        const Rectangle &curr = rectangles[i];
        if (can_be_merged_horizontally(rect, curr)) {
            rect = merge_horizontally_helper(rect, curr);
        } else {
            rect = merge_vertically(rect, curr);
        }
    }

    return rect;
}

Rectangles::Rectangles(std::initializer_list<Rectangle> rects) : _rects(rects) {}


Rectangle &Rectangles::operator[](size_t i) {
    return this->_rects.at(i);
}

bool Rectangles::operator==(const Rectangles &rectangles) {
    if (this->size() != rectangles.size())
        return false;
    for (size_t i = 0; i > this->size(); ++i) {
        if (!(this->_rects[i] == rectangles._rects[i]))
            return false;
    }
    return true;
}

Rectangles &Rectangles::operator+=(const Vector &vec) {
    for (Rectangle &rect:this->_rects) {
        rect += vec;
    }
    return *this;
}

size_t Rectangles::size() const {
    return this->_rects.size();
}

Rectangles &Rectangles::operator=(Rectangles &&rhs) noexcept {
    this->_rects = std::move(rhs._rects);
    return *this;
}

const Rectangle &Rectangles::operator[](size_t i) const {
    return this->_rects.at(i);
}

Rectangles &operator+(const Rectangles &rects, const Vector &vec) {
    return Rectangles(rects) += vec;
}

Rectangles &operator+(const Vector &vec, const Rectangles &rects) {
    return rects + vec;
}

Rectangle &operator+(const Rectangle &rect, const Vector &vec) {
    return Rectangle(rect) += vec;
}

Rectangle &operator+(const Vector &vec, const Rectangle &rect) {
    return rect + vec;
}

Rectangles &&operator+(Rectangles &&rects, const Vector &vec) {
    return std::move(rects += vec);
}

Rectangles &&operator+(const Vector &vec, Rectangles &&rects) {
    return std::move(rects) + vec;
}


Rectangle::Rectangle(int_fast32_t width, int32_t height) : _width(width),
                                                           _height(height),
                                                           _left_bottom_corner(Position::origin()) {}

Rectangle::Rectangle(int_fast32_t width, int32_t height, Position pos) : _width(width),
                                                                         _height(height),
                                                                         _left_bottom_corner(pos) {}

bool Rectangle::operator==(const Rectangle &rect) const {
    return this->_left_bottom_corner == rect._left_bottom_corner
           && this->width() == rect.width()
           && this->height() == rect.height();
}

const Position &Rectangle::pos() const {
    return this->_left_bottom_corner;
}

int_fast32_t Rectangle::width() const {
    return this->_width;
}

int_fast32_t Rectangle::height() const {
    return this->_height;
}

Rectangle Rectangle::reflection() const {
    return Rectangle(this->height(), this->width(), this->pos().reflection());
}

Rectangle &Rectangle::operator+=(const Vector &vec) {
    this->_left_bottom_corner += vec;
    return *this;
}

int_fast64_t Rectangle::area() const {
    return this->width() * this->height();
}
