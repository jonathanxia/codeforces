#pragma once

#include <lib/geo/convex_hull_indices.h>
#include <lib/geo/convex_polygon.h>

/**
 * WARNING: This has a bug and no longer gets AC after the redoing of the geometry
 * library.
 * 
 * This should probably get rewritten anyway.
 * 
 * Reference problem: https://codeforces.com/contest/1866/problem/K
*/
// An extension of the LineContainer from kactl.
// The LineContainer allows you to query the largest
// value of ax + b among a container of (a, b) pairs.
// This allows you to query the largest and second
// largest value of ax + b.
namespace geo {

template <typename T>
struct TwoLineContainer {
    ConvexPolygon<T> main_cvx_hull;
    umap<ll, ConvexPolygon<T>> secondary_cvx_hulls;

    TwoLineContainer() {}

    TwoLineContainer(const vector<Point<T>>& lines_) {
        vector<Point<T>> lines(lines_); // make a copy
        // sort our copy
        sort(ALL(lines));

        vi convex_indices = convex_hull_indices(lines, "upper");
        main_cvx_hull = ConvexPolygon<T>(vv::slc(lines, convex_indices), true);

        sort(ALL(convex_indices));
        if (len(convex_indices) == 0) return;

        walk(ci, convex_indices) {
            // Consider removing convex_indices[ci]
            // from the set.
            // Take all points with x coordinate from convex_indices[ci - 1]
            // to convex_indices[ci + 1] (inclusive), but
            // exclude convex_indices[ci] itself
            ll prev_idx = convex_indices[min(ci + 1, len(convex_indices) - 1)];
            ll next_idx = convex_indices[max(ci - 1, ll(0))];

            T prev_x = lines[prev_idx].x;
            T next_x = lines[next_idx].x;

            vector<Point<T>> pts;

            ll idx = convex_indices[ci] - 1;
            while (idx >= 0 && lines[idx].x >= prev_x) {
                pts.pb(lines[idx]);
                idx--;
            }
            idx = convex_indices[ci] + 1;
            while (idx < len(lines) && lines[idx].x <= next_x) {
                pts.pb(lines[idx]);
                idx++;
            }
            if (len(pts) > 0)
                secondary_cvx_hulls[ci] = ConvexPolygon(pts, false);
        }
    }

    // returns the two largest values of ax + b
    // if there is only one (a, b), the second value
    // is dflt_value
    pair<T, T> query(T x, T dflt_value) {
        if (len(main_cvx_hull) == 0) {
            return mp(dflt_value, dflt_value);
        }
        pair<T, T> ret = {dflt_value, dflt_value};
        auto res = main_cvx_hull.max_dot({x, T(1)});
        ret.first = res.second;
        ll idx = res.first;

        if (len(secondary_cvx_hulls) == 0) return ret;

        ret.second = secondary_cvx_hulls[idx].max_dot({x, T(1)}).second;
        return ret;
    }
};

} // namespace geo