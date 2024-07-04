#pragma once
#include <lib/common.h>

namespace vv {
// returns a sliced vector, a[start:end]
// endpoint inclusive (the slice is from [start, end])
template <typename T>
vector<T> slc(const vector<T>& a, int start = 0, int end = -1)
{
    if (start < 0) {
        start += len(a);
    }
    if (end < 0) {
        end += len(a);
    }
    return vector<T>(a.begin() + start, a.begin() + (end + 1));
}

// returns a subvector of a, defined by the indices in idx
template <typename T, typename S>
vector<T> slc(const vector<T>& a, const vector<S> idx)
{
    ll length = len(idx);
    vector<T> result(length);
    for (int i = 0; i < length; i++) {
        result[i] = a[idx[i]];
    }
    return result;
}
}