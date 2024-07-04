#pragma once
#include <lib/common.h>
namespace vv {
template <typename T>
T min(const vector<T>& a, int start = 0, int end = -1)
{
    if (start < 0) {
        start += len(a);
    }
    if (end < 0) {
        end += len(a);
    }

    T ans = a[start];
    FOR(i, start + 1, end)
    {
        ans = std::min(ans, a[i]);
    }
    return ans;
}


}