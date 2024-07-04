#pragma once
#include <lib/common.h>
namespace vv {
template <typename T>
T XOR(const vector<T>& a, int start = 0, int end = -1)
{
    if (end < 0) {
        end = len(a) + end;
    }
    T p(0);
    FOR(i, start, end)
    {
        p = p ^ a[i];
    }
    return p;
}


}