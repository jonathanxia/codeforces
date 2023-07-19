#include "common.h"

namespace geo {
template <typename T>
vector<pair<T, T>> convex_hull(vector<pair<T, T>>& points, bool top)
{
    ll n = len(points);
    stable_sort(ALL(points));

    vector<pair<T, T>> ret;
    ret.pb(points[0]);
    rep(i, 1, n - 1)
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
}