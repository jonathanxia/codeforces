#pragma once
#include <lib/common.h>
namespace vv {
// returns the index of the smallest element
// if earliest is true, then return the earliest smallest element when there is a tie.
template <typename T>
int argmin(const vector<T>& a, ll start = 0, ll end = -1, bool earliest = true)
{
    if (start < 0) {
        start += len(a);
    }
    if (end < 0) {
        end += len(a);
    }
    T best = a[start];
    int best_idx = start;
    FOR(i, start, end)
    {
        if (earliest ? (a[i] < best) : (a[i] <= best)) {
            best_idx = i;
            best = a[i];
        }
    }
    return best_idx;
}


}