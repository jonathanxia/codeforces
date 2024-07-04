#pragma once
#include <lib/common.h>
namespace vv {
template <typename T>
T sum(const vector<T>& a, int start = 0, int end = -1)
{
    if (end < 0) {
        end = len(a) + end;
    }
    if (start > end) return T(0);
    return std::accumulate(a.begin() + start, a.begin() + end + 1, T(0));
}
}