#include <lib/common.h>

namespace geo {
template <typename T>
vector<pair<T, T>> convex_hull(vector<pair<T, T>>& points, bool top)
{
    ll n = len(points);
    stable_sort(ALL(points));

    vector<pair<T, T>> ret;
    ret.pb(points[0]);
    FOR(i, 1, n - 1)
    {
        if (points[i] == ret.back())
            continue;
        while (len(ret) > 1) {
            ll L = len(ret);
            // slope0 = (ret[L - 1].y - ret[L - 2].y) / (ret[L - 1].x - ret[L - 2].x)
            // slope1 = (points[i].y - ret[L - 1].y) / (points[i].x - ret[L - 1].x)
            // if (slope0 <= slope1)
            T q1 = (points[i].first - ret[L - 1].first) * (ret[L - 1].second - ret[L - 2].second);
            T q2 = (points[i].second - ret[L - 1].second) * (ret[L - 1].first - ret[L - 2].first);
            if (top) {
                if (q1 <= q2)
                    ret.pop_back();
                else
                    break;
            } else {
                if (q1 >= q2)
                    ret.pop_back();
                else
                    break;
            }
        }
        ret.pb(points[i]);
    }
    return ret;
}
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
    bool operator<(P p) const { return tie(x, y) < tie(p.x, p.y); }
    bool operator==(P p) const { return tie(x, y) == tie(p.x, p.y); }
    P operator+(P p) const { return P(x + p.x, y + p.y); }
    P operator-(P p) const { return P(x - p.x, y - p.y); }
    P operator*(T d) const { return P(x * d, y * d); }
    P operator/(T d) const { return P(x / d, y / d); }
    T dot(P p) const { return x * p.x + y * p.y; }
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
        return os << "(" << p.x << "," << p.y << ")";
#endif
#endif
        return os << p.x << p.y;
    }
    friend istream& operator>>(istream& is, P& p)
    {
        is >> p.x >> p.y;
        return is;
    }
};
template <typename T>
vector<Point<T>> convex_hull(vector<Point<T>> pts)
{
    if (len(pts) <= 1)
        return pts;
    sort(ALL(pts));
    vector<Point<T>> h(len(pts) + 1);
    int s = 0, t = 0;
    for (int it = 2; it--; s = --t, reverse(ALL(pts)))
        for (Point<T> p : pts) {
            while (t >= s + 2 && h[t - 2].cross(h[t - 1], p) <= 0)
                t--;
            h[t++] = p;
        }
    return { h.begin(), h.begin() + t - (t == 2 && h[0] == h[1]) };
}
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
template <class P>
double line_dist(const P& a, const P& b, const P& p)
{
    return (double)(b - a).cross(p - a) / (b - a).dist();
}
// Two lines, one through s1, e1 and the other through s2, e2. If they have
// a unique intersection, then returns {1, intersection}.
// If no intersection, returns {0, (0, 0)}.
// If infinitely many, returns {-1, (0, 0)}.
template <class P>
pair<int, P> line_intersect(P s1, P e1, P s2, P e2)
{
    auto d = (e1 - s1).cross(e2 - s2);
    if (d == 0) // if parallel
        return { -(s1.cross(e1, s2) == 0), P(0, 0) };
    auto p = s2.cross(e1, e2), q = s2.cross(e2, s1);
    return { 1, (s1 * p + e1 * q) / d };
}
// Returns the shortest distance between point p and the segment from s to e.
template <class P>
double seg_dist(P& s, P& e, P& p)
{
    if (s == e)
        return (p - s).dist();
    auto d = (e - s).dist2(), t = min(d, max(.0, (p - s).dot(e - s)));
    return ((p - s) * d - (e - s) * t).dist() / d;
}
}