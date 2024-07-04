#pragma once
#include <lib/common.h>

namespace vv {
template <typename S, typename T>
int indexof(const vector<T>& a, const S& element)
{
    for (int i = 0; i < len(a); ++i) {
        if (a[i] == element) {
            return i;
        }
    }
    return -1;
}
} // namespace vv