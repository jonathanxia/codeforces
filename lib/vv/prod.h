#pragma once
#include <lib/common.h>
namespace vv {
template <typename T>
T prod(const vector<T>& a, int start = 0, int end = -1, ll mm = -1)
{
    if (end < 0) {
        end = len(a) + end;
    }
    T p(1);
    FOR(i, start, end)
    {
        p = p * a[i];
        if (mm > 0) {
            p %= mm;
        }
    }
    return p;
}


}