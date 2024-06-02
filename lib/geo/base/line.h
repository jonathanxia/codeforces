#pragma once
#include <lib/geo/base/point.h>

namespace geo {
// ax+by+c = 0
template <typename T>
struct Line {
  T a, b, c;

  Line(T a_, T b_, T c_) : a(a_), b(b_), c(c_) {}
  Line(Point<T> A, Point<T> B) {
    a = A.y - B.y, b = B.x - A.x, c = A.x * B.y - A.y * B.x;
  }
  Line(T x1, T y1, T x2, T y2) : Line(Point<T>(x1, y1), Point<T>(x2, y2)) {}

  template <typename U>
  U eval(Point<U> P) {
    return a * P.x + b * P.y + c;
  }

  template <typename U>
  T eval(U x, U y) {
    return a * x + b * y + c;
  }

  void normalize() {
    static_assert(is_same_v<T, int> || is_same_v<T, long long>);
    T g = gcd(gcd(abs(a), abs(b)), abs(c));
    a /= g, b /= g, c /= g;
    if (b < 0) { a = -a, b = -b, c = -c; }
    if (b == 0 && a < 0) { a = -a, b = -b, c = -c; }
  }

  bool is_parallel(Line other) { return a * other.b - b * other.a == 0; }
  bool is_orthogonal(Line other) { return a * other.a + b * other.b == 0; }

  friend ostream& operator<<(ostream& os, Line line) {
    return os << line.a << "x + " << line.b << "y + " << line.c << " = 0";
  }
};

template <typename T>
struct Segment {
  Point<T> A, B;

  Segment(Point<T> A_, Point<T> B_) : A(A_), B(B_) {}
  Segment(T x1, T y1, T x2, T y2)
      : Segment(Point<T>(x1, y1), Point<T>(x2, y2)) {}

  bool contains(Point<T> C) {
    static_assert(is_integral<T>::value);
    T det = (C - A).det(B - A);
    if (det != 0) return 0;
    return (C - A).dot(B - A) >= 0 && (C - B).dot(A - B) >= 0;
  }

  Line<T> to_Line() { return Line(A, B); }
  
  double norm() { return dist<double>(A, B); }

    // If a unique intersection point between this segment and other segment then that intersection is returned
    // If no intersection point exists an empty vector is returned. If infinitely many exist a vector with 2 elements is returned, containing the endpoints of the common line segment.
    // The wrong position will be returned if P is Point<ll> and the intersection point does not have integer coordinates.
    // Products of three coordinates are used in intermediate steps so watch out for overflow if using int or long long.
    vector<Point<T>> intersect(Segment<T> other)
    {
        Point<T>& C = other.A;
        Point<T>& D = other.B;
        auto oa = C.cross(D, A), ob = C.cross(D, B),
            oc = A.cross(B, C), od = A.cross(B, D);
        // Checks if intersection is single non-endpoint point.
        if (sgn(oa) * sgn(ob) < 0 && sgn(oc) * sgn(od) < 0)
            return {(A * ob - B * oa) / (ob - oa)};
        set<Point<T>> s;
        if (other.contains(A)) s.insert(A);
        if (other.contains(B)) s.insert(B);
        if (this->contains(C)) s.insert(C);
        if (this->contains(D)) s.insert(D);
        return {ALL(s)};
    }

    // Same interface as intersect(Segment) but for a Line
    vector<Point<T>> intersect(Line<T> other) {
        vector<Point<T>> ret;
        auto oa = other.eval(A);
        auto ob = other.eval(B);
        if ((oa > 0 && ob > 0) || (oa < 0 && ob < 0)) return ret;
        // Check if both are 0
        if (oa == 0 && ob == 0) return {A, B};
        // This means that they intersect so we can just compute
        // what the intersection is now
        return {(A * ob - B * oa) / (ob - oa)};
    }

  friend ostream& operator<<(ostream& os, Segment seg) {
    return os << "Segment(" << seg.A << "--" << seg.B << ")";
  }
};


} // namespace geo