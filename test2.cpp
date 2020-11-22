#include "geometry.h"
#include <utility>
#include <iostream>

#ifdef NDEBUG
#undef NDEBUG
#endif // NDEBUG

#include <cassert>

int main() {
    Rectangles tm1{Rectangle(8, 1, {-4, 8}),
                   Rectangle(71, 23, {5, 6}),
                   Rectangle(9, 15, {43, 12})};

    Rectangles tm2{Rectangle(8, 1, {-4, 8}),
                   Rectangle(71, 23, {5, 6}),
                   Rectangle(9, 15, {43, 12})};

    Rectangles tm3{Rectangle(8, 1, {-4, 8}),
                   Rectangle(71, 23, {5, 6}),
                   Rectangle(9, 15, {43, 12})};

    Rectangles tm4{Rectangle(8, 1, {-4, 8}),
                   Rectangle(71, 23, {5, 6}),
                   Rectangle(9, 15, {43, 12})};

    Rectangles result{Rectangle(8, 1, {-25, 42}),
                      Rectangle(71, 23, {-16, 40}),
                      Rectangle(9, 15, {22, 46})};

    Rectangles result2{Rectangle(8, 1, {8, 13}),
                       Rectangle(71, 23, {17, 11}),
                       Rectangle(9, 15, {55, 17})};

    Vector v{12, 5};
    const Vector cv{-21, 34};

    Rectangles r1 = std::move(tm1) + cv;
    Rectangles r2 = cv + std::move(tm2);
    Rectangles r3 = std::move(tm3) + v;
    Rectangles r4 = v + std::move(tm4);

    assert(r1 == result);
    assert(r2 == result);
    assert(r3 == result2);
    assert(r4 == result2);

    std::cout << "Test passed!" << std::endl;
}