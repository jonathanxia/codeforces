#pragma once
#include <lib/geo/base/point.h>
#include <lib/geo/base/line.h>

namespace geo {
    template <typename T>
    struct Polygon {
    vector<Point<T>> points;
    T m_area;

    template <typename A, typename B>
    Polygon(vector<pair<A, B>> pairs) {
        for (auto&& [a_, b]: pairs) points.eb(Point<T>(a_, b));
        build();
    }
    Polygon(vector<Point<T>> points_) : points(points_) { build(); }

    int size() { return len(points); }

    // NOTE: You must call this with the template argument so it knows
    // what type to return
    template <typename REAL>
    REAL area() {
        return m_area * 0.5;
    }

    T area_2() {
        return m_area;
    }

    bool is_convex() {
        FOR(j, 0, len(points) - 1) {
        int i = (j == 0 ? len(points) - 1 : j - 1);
        int k = (j == len(points) - 1 ? 0 : j + 1);
        if ((points[j] - points[i]).det(points[k] - points[j]) < 0) return false;
        }
        return true;
    }

    template <typename REAL>
    REAL perimeter() {
        REAL ans(0);
        walk(i, points) {
            ll j = i + 1;
            j = j >= len(points) ? j - len(points) : j;
            ans += (points[j] - points[i]).norm();
        }
        return ans;
    }

    // Returns true if a lies within. If strict is true, returns false for
    // boundary points.
    // Runtime: O(n)
    bool contains(Point<T> a, bool strict = true)
    {
        int cnt = 0, n = len(points);
        FOR(i, 0, n - 1)
        {
            Point<T> q = points[(i + 1) % n];
            if (Segment<T>(points[i], q).contains(a))
                return !strict;
            // or: if (segDist(p[i], q, a) <= eps) return !strict;
            cnt ^= ((a.y < points[i].y) - (a.y < q.y)) * a.cross(points[i], q) > 0;
        }
        return cnt;
    }

    private:
    void build() {
        m_area = 0;
        FOR(i, 0, len(points) - 1) {
        int j = (i + 1 == len(points) ? 0 : i + 1);
        m_area += points[i].det(points[j]);
        }
        if (m_area < 0) {
        m_area = -m_area;
        reverse(ALL(points));
        }
    }
    };
} // namespace geo