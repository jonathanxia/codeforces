/**
 * Base objects for geometry: Point
*/
#pragma once
#include <lib/common.h>

namespace geo {
    // We define the REAL type here, where you can change this in
    // later. Basically, Point, Line, etc can be integers if you want, but
    // some concepts require going to the real numbers, such as area and perimeter.
    using REAL=long double;

template <class T>
int sgn(T x) { return (x > 0) - (x < 0); }

template <class T>
struct Point {
    typedef Point P;
    T x, y;

    // Constructors ----
    Point() : x(0), y(0) {}
    template <typename A>
    Point(A x_) : x(x_), y(0) {}
    template <typename A, typename B>
    Point(A x_, B y_) : x(x_), y(y_) {}

    Point(initializer_list<T> values) : x(values.begin()[0]), y(values.begin()[1]) {}

    template <typename A, typename B>
    Point(pair<A, B> p) : x(p.first), y(p.second) {}

    // Arithmetic operators ------
    P operator+(P p) const { return P(x + p.x, y + p.y); }
    P operator-(P p) const { return P(x - p.x, y - p.y); }
    P operator*(T d) const { return P(x * d, y * d); }
    P operator/(T d) const { return P(x / d, y / d); }
    P operator-() const { return {-x, -y}; }
    void operator+=(P p) { x += p.x; y += p.y; }
    void operator-=(P p) { x -= p.x; y -= p.y; }
    void operator*=(T d) const { x *= d; y *= d; } 
    void operator/=(T d) const { x /= d; y /= d; } 

    // Comparison operators -----
    bool operator==(Point p) const { return x == p.x && y == p.y; }
    bool operator!=(Point p) const { return x != p.x || y != p.y; }
    bool operator<(Point p) const {
        if (x != p.x) return x < p.x;
        return y < p.y;
    }
    bool operator<=(P p) const { return *this < p || *this == p; }
    bool operator>=(P p) const { return !(*this < p); }
    bool operator>(P p) const { return !(*this <= p); }

    // Descriptive methods
    REAL norm() { return sqrtl(x * x + y * y); }

    T dist2() const { return x * x + y * y; }

    REAL dist() const { return sqrt(REAL(dist2())); }

    // angle to x-axis in interval [-pi, pi]
    REAL angle() const { return atan2(y, x); }

    T dot(P p) const { return x * p.x + y * p.y; }
    T cross(P p) const { return x * p.y - y * p.x; }
    T det(P p) const { return x * p.y - y * p.x; } // Same as cross()
    T cross(P a, P b) const { return (a - *this).cross(b - *this); }

    P unit() const { return *this / dist(); } // makes dist()=1
    P perp() const { return P(-y, x); } // rotates +90 degrees
    P normal() const { return perp().unit(); }

    // returns point rotated 'theta' radians ccw around the origin
    P rotate(double theta) const
    {
        static_assert(!is_integral<T>::value);
        return P(x * cos(theta) - y * sin(theta), x * sin(theta) + y * cos(theta));
    }

    // Printing operators
    friend ostream& operator<<(ostream& os, P p)
    {
#ifndef ONLINE_JUDGE
#ifdef DEBUG
        return os << "(" << p.x << ", " << p.y << ")";
#else
        return os << p.x << " " << p.y;
#endif
#else
        return os << p.x << " " << p.y;
#endif
    }
    friend istream& operator>>(istream& is, P& p)
    {
        is >> p.x >> p.y;
        return is;
    }
};

// A -> B -> C is ccw -> +1, otherwise returns -1
template <typename T>
int ccw(Point<T> A, Point<T> B, Point<T> C) {
  T x = (B - A).det(C - A);
  if (x > 0) return 1;
  if (x < 0) return -1;
  return 0;
}

template <typename T>
REAL dist(Point<T> A, Point<T> B) {
  A = A - B;
  T p = A.dot(A);
  return sqrt(REAL(p));
}

} // namespace geo