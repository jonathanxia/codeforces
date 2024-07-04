#pragma once
#include <lib/common.h>

namespace vv {
template <typename T>
unordered_map<T, ll, custom_hash> counter(const vector<T>& a, ll start = 0, ll end = -1)
{
    if (start < 0) {
        start += len(a);
    }
    if (end < 0) {
        end += len(a);
    }

    unordered_map<T, ll, custom_hash> result;
    FOR(i, start, end)
    {
        result[a[i]]++;
    }

    return result;
}
}