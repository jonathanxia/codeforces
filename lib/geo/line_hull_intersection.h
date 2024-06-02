#pragma once

#include <lib/common.h>
#include <lib/geo/basic.h>
#include <lib/geo/convex_polygon.h>

namespace geo {
/**
 * Intersects a line with a convex polygon.
 * lineHull(line, poly) returns a pair describing the intersection of a line with the polygon:
 *  \begin{itemize*}
 *    \item $(-1, -1)$ if no collision,
 *    \item $(i, -1)$ if touching the corner $i$,
 *    \item $(i, i)$ if along side $(i, i+1)$,
 *    \item $(i, j)$ if crossing sides $(i, i+1)$ and $(j, j+1)$.
 *  \end{itemize*}
 *  In the last case, if a corner $i$ is crossed, this is treated as happening on side $(i, i+1)$.
 *  The points are returned in the same order as the line hits the polygon.
 * Time: O(\log n)
 * Usage: https://atcoder.jp/contests/abc356/submissions/54148710
 */
template <typename T>
array<int, 2> lineHullIntersection(const ConvexPolygon<T>& poly, Point<T> a, Point<T> b) {
    int endA = poly.max_dot((a - b).perp()).first;
    int endB = poly.min_dot((a - b).perp()).first;

    // This says which side of a--b it is.
    auto cmpL = [&poly, &a, &b](int i) {
        return sgn(a.cross(poly.points[i], b));
    };

    // There is no intersection
	if (cmpL(endA) < 0 || cmpL(endB) > 0)
		return {-1, -1};

	array<int, 2> res;
	FOR(i, 0, 1) {
        // Binary search on where the polygon crosses the line a--b
		int lo = endB, hi = endA, n = poly.n;
		while ((lo + 1) % n != hi) {
			int m = ((lo + hi + (lo < hi ? 0 : n)) / 2) % n;
			(cmpL(m) == cmpL(endB) ? lo : hi) = m;
		}
		res[i] = (lo + !cmpL(hi)) % n;
		swap(endA, endB);
	}
	if (res[0] == res[1]) return {res[0], -1};
	if (!cmpL(res[0]) && !cmpL(res[1]))
		switch ((res[0] - res[1] + len(poly) + 1) % len(poly)) {
			case 0: return {res[0], res[0]};
			case 2: return {res[1], res[1]};
		}
	return res;
}


/**
 * Intersects a line with a ConvexPolygon and returns a vector of intersection points.
 * 
 * Usage: https://atcoder.jp/contests/abc356/submissions/54148710
*/
template <typename T>
vector<Point<T>> lineHullIntersectionPoints(const ConvexPolygon<T>& poly, Point<T> a, Point<T> b) {
    auto indices = lineHullIntersection(poly, a, b);
    vector<Point<T>> output;
    Line<T> line(a, b);
    foreach(idx, indices) {
        if (idx < 0) continue;
        ll i = idx;
        ll j = (idx + 1) % poly.n;
        auto inters = Segment<T>(poly.points[i], poly.points[j]).intersect(line);
        foreach(inter, inters) output.pb(inter);
    }
    return output;
}
} // namespace geo
