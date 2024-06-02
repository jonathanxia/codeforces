#pragma once
#include <lib/vv.h>
#include <lib/geo/convex_hull_indices.h>

/**
 * The ConvexPolygon<T> object stores a convex polygon with vertices of type Point<T>.
 * The points are stored in ccw order and can be accessed through the `points` attribute.
*/
namespace geo {
template <typename T>
struct ConvexPolygon
{
    using P = Point<T>;
    template <typename G>
    using vc = vector<G>;

    int n;
    vc<P> points;

    ConvexPolygon(vc<P> points_, bool is_conv) : n(len(points_)), points(points_)
    {
        if (!is_conv)
        {
            vc<int> I = convex_hull_indices<T>(points_, "full");
            points = vv::slc(points_, I);
            n = len(points);
        }
        // assert(n >= 3);
        // Make sure that this is counterclockwise
        if (n >= 3)
        {
            if ((points[1] - points[0]).det(points[2] - points[0]) < 0)
            {
                reverse(ALL(points));
            }
        }
    }

    // comp is a function comp(i, j) that compares two indices
    template <typename F>
    int periodic_min_comp(F comp) const
    {
        int L = 0, M = n, R = n + n;
        while (1)
        {
            if (R - L == 2)
                break;
            int L1 = (L + M) / 2, R1 = (M + R + 1) / 2;
            if (comp(L1, M))
            {
                R = M, M = L1;
            }
            else if (comp(R1, M)) { L = M, M = R1; }
            else
            {
                L = L1, R = R1;
            }
        }
        return M % n;
    }

    int nxt_idx(int i) const { return (i + 1 == n ? 0 : i + 1); }
    int prev_idx(int i) const { return (i == 0 ? n - 1 : i - 1); }

    // Whether points p is inside the polygon.
    // -1 if outside, 1 if inside, 0 if on boundary
    int side(P p)
    {
        int L = 1, R = n - 1;
        T a = (points[L] - points[0]).det(p - points[0]);
        T b = (points[R] - points[0]).det(p - points[0]);
        if (a < 0 || b > 0)
            return -1;
        while (R - L >= 2)
        {
            int M = (L + R) / 2;
            T c = (points[M] - points[0]).det(p - points[0]);
            if (c < 0)
                R = M, b = c;
            else
                L = M, a = c;
        }
        T c = (points[R] - points[L]).det(p - points[L]);
        T x = min({a, -b, c});
        if (x < 0)
            return -1;
        if (x > 0)
            return 1;
        return 0;
    }

    /**
     * Returns the points with minimum dot product with p
     */
    pair<int, T> min_dot(P p) const
    {
        int idx = periodic_min_comp([&](int i, int j) -> bool
                                    { return points[i % n].dot(p) < points[j % n].dot(p); });
        return {idx, points[idx].dot(p)};
    }

    /**
     * Returns the points with maximum dot product with p
     */
    pair<int, T> max_dot(P p) const
    {
        int idx = periodic_min_comp([&](int i, int j) -> bool
                                    { return points[i % n].dot(p) > points[j % n].dot(p); });
        return {idx, points[idx].dot(p)};
    }

    int size() const { return n; }
};
} //namespace geo