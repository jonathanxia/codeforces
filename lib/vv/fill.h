#pragma once
#include <lib/common.h>
namespace vv {
template <typename S, typename T>
void fill(vector<T>& a, S elem)
{
    FOR(i, 0, len(a) - 1)
    {
        a[i] = elem;
    }
}


}