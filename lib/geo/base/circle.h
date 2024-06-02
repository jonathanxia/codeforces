#pragma once
#include <lib/geo/base/point.h>

namespace geo {
    template <typename REAL>
    struct Circle {
        Point<REAL> O;
        REAL r;
        Circle(Point<REAL> O_, REAL r_) : O(O_), r(r_) {}
        Circle(REAL x, REAL y, REAL r_) : O(x, y), r(r_) {}
        template <typename T>
        bool contain(Point<T> p) {
            REAL dx = p.x - O.x, dy = p.y - O.y;
            return dx * dx + dy * dy <= r * r;
        }
    }; // struct Circle
} // namespace geo