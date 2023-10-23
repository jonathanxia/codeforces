#include <lib/vv.h>

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
}