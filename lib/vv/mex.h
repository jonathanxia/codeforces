#pragma once
#include <lib/common.h>

namespace vv {
template <typename T>
ll mex(const vector<T>& a, bool positive=false) {
    ll n = len(a);
    ll start = int(positive);
    vb exists(start + n);
    FOR(i, 0, n - 1) {
        if (a[i] >= n + start) continue;
        exists[a[i]] = true;
    }
    FOR(i, start, n - 1 + start) {
        if (!exists[i]) return i;
    }
    return n + start;
}
}