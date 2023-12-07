#include <lib/common.h>

namespace geo {
template <class T>
int sgn(T x) { return (x > 0) - (x < 0); }
template <class T>
struct Point {
    typedef Point P;
    T x, y;
    explicit Point(T x_ = 0, T y_ = 0)
        : x(x_)
        , y(y_)
    {
    }
    // Wow c++ is bad with initializer_list...
    Point(initializer_list<T> values) : x(values.begin()[0]), y(values.begin()[1]) {}
    bool operator<(P p) const { return tie(x, y) < tie(p.x, p.y); }
    bool operator==(P p) const { return tie(x, y) == tie(p.x, p.y); }
    P operator+(P p) const { return P(x + p.x, y + p.y); }
    P operator-(P p) const { return P(x - p.x, y - p.y); }
    P operator*(T d) const { return P(x * d, y * d); }
    P operator/(T d) const { return P(x / d, y / d); }
    T dot(P p) const {
        return x * p.x + y * p.y;
    }
    T cross(P p) const { return x * p.y - y * p.x; }
    T cross(P a, P b) const { return (a - *this).cross(b - *this); }
    T dist2() const { return x * x + y * y; }
    double dist() const { return sqrt((double)dist2()); }
    // angle to x-axis in interval [-pi, pi]
    double angle() const { return atan2(y, x); }
    P unit() const { return *this / dist(); } // makes dist()=1
    P perp() const { return P(-y, x); } // rotates +90 degrees
    P normal() const { return perp().unit(); }
    // returns point rotated 'a' radians ccw around the origin
    P rotate(double a) const
    {
        return P(x * cos(a) - y * sin(a), x * sin(a) + y * cos(a));
    }
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

template <typename T>
struct ConvexHull {
    // All points of the convex hull
    vector<Point<T>> points;
    vi indices; // The indices in the original given list
    vi index_to_loc; // index to location within the convex hull

    vb is_top; // whether this point is on the top of the cvx hull
    vb is_bottom; // whether this point is on the bottom of the cvx hull

    // Indices used to indicate how to iterate over half the cvx hull
    int top_start_;
    int top_end_;
    int bot_start_;
    int bot_end_;

    ConvexHull() {} // dflt ctor

    ConvexHull(const vector<Point<T>>& pts_)
    {
        ll n = len(pts_);
        if (len(pts_) <= 1) {
            points = pts_;
            indices = vi(n, 0);
            index_to_loc = vi(n, 0);
            is_top = vb(n, true);
            is_bottom = vb(n, true);
            top_start_ = top_end_ = bot_start_ = bot_end_ = 0;
            return;
        }

        vector<pair<Point<T>, int>> pts;
        FOR(i, 0, n - 1) {
            pts.pb({pts_[i], i});
        }

        sort(ALL(pts));
        vector<pair<Point<T>, int>> h(len(pts) + 1);

        vi iteration_num(n, 0);

        int start = 0, t = 0;
        for (int it = 2; it--; start = --t, reverse(ALL(pts))) {
            for (auto p : pts) {
                while (t >= start + 2 && h[t - 2].first.cross(h[t - 1].first, p.first) <= 0)
                    t--;
                h[t++] = p;
            }
            FOR(i, start, t - 1) {
                iteration_num[h[i].second] |= (1 << it);
            }
        }
        vector<pair<Point<T>, int>> cvx_hull = { h.begin(), h.begin() + t - (t == 2 && h[0].first == h[1].first) };
        foreach(v, cvx_hull) points.pb(v.first);
        foreach(v, cvx_hull) indices.pb(v.second);
        foreach(v, cvx_hull) is_top.pb(iteration_num[v.second] & 1);
        foreach(v, cvx_hull) is_bottom.pb(iteration_num[v.second] & 2);

        n = len(cvx_hull);
        index_to_loc.resize(len(pts_));
        FOR(i, 0, len(cvx_hull) - 1) index_to_loc[indices[i]] = i;

        bot_start_ = 0;
        bot_end_ = first_st(i, !is_bottom[i], 0, n - 1) - 1;
        top_start_ = bot_end_;
        top_end_ = first_st(i, !is_top[i % n], top_start_, top_start_ + n - 1) - 1;
    }

    // Returns the index of the point with the highest value of
    // ax + b across all points (a, b) in the convex hull
    int query_highest_index(T x) {
        // The top portion of the convex hull should be decreasing in
        // x value
        ll n = len(points);
        if (n == 0) return -1;
        Point<T> p = {x, 1};
        if (n == 1) return 0;
        if (top_start_ == top_end_) {
            return top_start_ % n;
        }

        ll cvx_idx = smallest_st(
            i, p.dot(points[i % n]) > p.dot(points[(i + 1) % n]),
            top_start_, top_end_ - 1);
        
        return indices[cvx_idx % n];
    }

    // Returns the highest value of ax + b across all points (a, b)
    // in the convex hull
    T query_highest(T x) {
        ll idx = query_highest_index(x);
        if (idx < 0) return std::numeric_limits<T>::min();
        Point<T> optimal = points[index_to_loc[idx]];
        return optimal.dot({x, 1});
    }

    // Returns the index of the point with the smallest value of
    // ax + b across all points (a, b) in the convex hull
    int query_smallest_index(T x) {
        // The bottom portion of the convex hull should be increasing in
        // x value
        ll n = len(points);
        if (n == 0) return -1;
        if (n == 1) return 0;
        Point<T> p = {x, 1};
        if (bot_start_ == bot_end_) {
            return bot_start_ % n;
        }

        // This means the dot product should go down then up

        ll cvx_idx = smallest_st(
            i, p.dot(points[i % n]) < p.dot(points[(i + 1) % n]),
            bot_start_, bot_end_ - 1);

        return indices[cvx_idx % n];
    }

    // Returns the smallest value of ax + b across all points (a, b)
    // in the convex hull
    T query_smallest(T x) {
        ll idx = query_smallest_index(x);
        if (idx < 0) return std::numeric_limits<T>::max();
        Point<T> optimal = points[index_to_loc[idx]];
        return optimal.dot({x, 1});
    }

    friend ostream& operator<<(ostream& os, const ConvexHull& p)
    {
        return os << p.points;
    }
};

// An extension of the LineContainer from kactl.
// The LineContainer allows you to query the largest
// value of ax + b among a container of (a, b) pairs.
// This allows you to query the largest and second
// largest value of ax + b.
template <typename T>
struct TwoLineContainer {
    ConvexHull<T> main_cvx_hull;
    umap<ll, ConvexHull<T>> secondary_cvx_hulls;

    TwoLineContainer() {}

    TwoLineContainer(const vector<Point<T>>& lines_) {
        vector<Point<T>> lines(lines_); // make a copy
        // sort our copy
        sort(ALL(lines));

        main_cvx_hull = ConvexHull(lines);
        vi convex_indices;
        walk(ci, main_cvx_hull.indices) {
            if (main_cvx_hull.is_top[ci])
                convex_indices.pb(main_cvx_hull.indices[ci]);
        }

        sort(ALL(convex_indices));
        if (len(convex_indices) == 0) return;

        walk(ci, convex_indices) {
            // Consider removing convex_indices[ci]
            // from the set.
            // Take all points with x coordinate from convex_indices[ci - 1]
            // to convex_indices[ci + 1] (inclusive), but
            // exclude convex_indices[ci] itself
            ll prev_idx = convex_indices[max(ci - 1, ll(0))];
            ll next_idx = convex_indices[min(ci + 1, len(convex_indices) - 1)];

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
                secondary_cvx_hulls[convex_indices[ci]] = ConvexHull(pts);
        }
    }

    // returns the two largest values of ax + b
    // if there is only one (a, b), the second value
    // is dflt_value
    pair<T, T> query(T x, T dflt_value) {
        if (len(main_cvx_hull.points) == 0) {
            return mp(dflt_value, dflt_value);
        }
        pair<T, T> ret = {dflt_value, dflt_value};
        ret.first = main_cvx_hull.query_highest(x);

        if (len(secondary_cvx_hulls) == 0) return ret;

        ll idx = main_cvx_hull.query_highest_index(x);
        ret.second = secondary_cvx_hulls[idx].query_highest(x);

        return ret;
    }
};

template <typename T>
T polygon_perimeter(vector<Point<T>> pts)
{
    ll n = len(pts);
    T perimeter = 0;
    walk(i, pts)
    {
        Point<T> displacement = pts[i] - pts[mod(i - 1, n)];
        perimeter += displacement.dist();
    }
    return perimeter;
}
// Returns the signed distance between point p and the line containing points
// a and b. Positive value on left side and negative on right as seen from
// a towards b. a==b gives nan. P is supposed to be Point<T>.
template <typename T>
double line_dist(const Point<T>& a, const Point<T>& b, const Point<T>& p)
{
    return (double)(b - a).cross(p - a) / (b - a).dist();
}
// Two lines, one through s1, e1 and the other through s2, e2. If they have
// a unique intersection, then returns {1, intersection}.
// If no intersection, returns {0, (0, 0)}.
// If infinitely many, returns {-1, (0, 0)}.
template <typename T>
pair<int, Point<T>> line_intersect(Point<T> s1, Point<T> e1, Point<T> s2, Point<T> e2)
{
    auto d = (e1 - s1).cross(e2 - s2);
    if (d == 0) // if parallel
        return { -(s1.cross(e1, s2) == 0), Point<T>(0, 0) };
    auto p = s2.cross(e1, e2), q = s2.cross(e2, s1);
    return { 1, (s1 * p + e1 * q) / d };
}
// Returns the shortest distance between point p and the segment from s to e.
template <typename T>
double seg_dist(Point<T>& s, Point<T>& e, Point<T>& p)
{
    if (s == e)
        return (p - s).dist();
    auto d = (e - s).dist2(), t = min(d, max(.0, (p - s).dot(e - s)));
    return ((p - s) * d - (e - s) * t).dist() / d;
}
// Returns whether p is on the segment from s to e.
template <typename T>
bool on_segment(Point<T> s, Point<T> e, Point<T> p)
{
    return p.cross(s, e) == 0 && (s - p).dot(e - p) <= 0;
}
// Returns **twice** the signed area of polygon defined by v.
// Must provide a vector with either cw or ccw enumeration.
template <class T>
T polygon_area2(vector<Point<T>>& v)
{
    T a = v.back().cross(v[0]);
    repe(i, 0, len(v) - 1) a += v[i].cross(v[i + 1]);
    return a;
}
// Returns true if a lies within p. If strict is true, returns false for
// boundary points.
template <typename T>
bool in_polygon(vector<Point<T>>& p, Point<T> a, bool strict = true)
{
    int cnt = 0, n = len(p);
    repe(i, 0, n)
    {
        Point<T> q = p[(i + 1) % n];
        if (on_segment(p[i], q, a))
            return !strict;
        // or: if (segDist(p[i], q, a) <= eps) return !strict;
        cnt ^= ((a.y < p[i].y) - (a.y < q.y)) * a.cross(p[i], q) > 0;
    }
    return cnt;
}
} // namespace geo

