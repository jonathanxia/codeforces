#pragma once
#include <lib/common.h>
#include <lib/vv/max.h>
#include <lib/cum.h>
#include <lib/vv/sort.h>

namespace intervals {

// Assumes inclusive intervals
// Returns `[exists, interval]`
// `exists`: bool on whether there exists an interval that is included in all intervals
// `interval`: the interval that is included in all intervals. Can be anything if `exists` is false
template <class T>
pair<bool, pair<T, T>> intersection(const vector<pair<T, T>>& intervals_list)
{
    auto [l, r] = intervals_list[0];
    walk(i, intervals_list)
    {
        if (i == 0)
            continue;
        chkmax(l, intervals_list[i].first);
        chkmin(r, intervals_list[i].second);
    }
    return { l <= r, { l, r } };
}

// Assumes inclusive intervals
// Makes intervals_list a disjoint set of intervals that covers the same points that it did originally
// Performs in-place.
template <class T>
void unify(vector<pair<T, T>>& intervals_list)
{
    if (intervals_list.empty())
        return;
    sort(ALL(intervals_list));
    ll idx_of_back = 0;
    rep(i, 1, len(intervals_list))
    {
        // Interval is disjoint from the previous one
        if (intervals_list[i].first > intervals_list[idx_of_back].second) {
            idx_of_back++;
            intervals_list[idx_of_back] = intervals_list[i];
        } else {
            chkmin(intervals_list[idx_of_back].first, intervals_list[i].first);
            chkmax(intervals_list[idx_of_back].second, intervals_list[i].second);
        }
    }
    intervals_list.resize(idx_of_back + 1);
}

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

    vv::sort(events);

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

    return vv::max(cum::sum(cumulative).cum_data);
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