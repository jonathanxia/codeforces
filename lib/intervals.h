#pragma once
#include <lib/common.h>

namespace intervals {

// Returns the maximum number of intervals
// covering some point from a bunch of intervals.
// The intervals are inclusive in both start and end
ll max_coverage(const vpl& intervals) {
    ll m = len(intervals);
    if (m == 0) return 0;
    vpl events;
    FOR(i, 0, m - 1) {
        events.pb({intervals[i].first, 1});
        events.pb({intervals[i].second + 1, -1});
    }

    sort(events);

    // Collapse into singletons I guess?
    vl cumulative;
    ll prev = -1e18;
    FOR(i, 0, len(events) - 1) {
        if (events[i].first == prev) {
            cumulative.back() += events[i].second;
        }
        else {
            cumulative.pb(events[i].second);
        }

        prev = events[i].first;
    }

    return max(cumsum(cumulative));
}
// Minimum number of intervals in I needed to cover G. Returns a vector of
// indices pointing to intervals in I in the minimal covering. Returns empty
// vector if covering is not possible.
template <class T>
vi min_cover(vector<pair<T, T>> I, pair<T, T> G)
{
    vi S(sz(I)), R;
    iota(ALL(S), 0);
    sort(ALL(S), [&](int a, int b) { return I[a] < I[b]; });
    T cur = G.first;
    int at = 0;
    while (cur < G.second) { // (A)
        pair<T, int> mx = make_pair(cur, -1);
        while (at < sz(I) && I[S[at]].first <= cur) {
            mx = max(mx, make_pair(I[S[at]].second, S[at]));
            at++;
        }
        if (mx.second == -1)
            return {};
        cur = mx.first;
        R.push_back(mx.second);
    }
    return R;
}
}