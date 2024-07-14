#pragma once
#include <lib/common.h>

namespace vv {
    // Computes mex(a)
    // :param positive: If true, then finds the first positive number not in a
    //     otherwise it is the first non-negative number not in a
    // :param k: Computes the k-th non-negative number not in a
    //     (or k-th positive number if positive is true)
template <typename T>
ll mex(const vector<T>& a, bool positive=false, int k=1) {
    ll n = len(a);
    ll start = int(positive);
    vb exists(start + n + k + 1);
    FOR(i, 0, n - 1) {
        if (a[i] >= len(exists)) continue;
        exists[a[i]] = true;
    }
    ll num_seen = 0;
    ll i = start - 1;
    do {
        i++;
        if (!exists[i]) num_seen++;
    } while (num_seen < k);
    return i;
}
}