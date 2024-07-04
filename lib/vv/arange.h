#pragma once
#include <lib/common.h>

namespace vv {
template <typename T>
inline vector<T> arange(T start, T end, T step = 1)
{
    vector<T> result;
    for (T value = start; value <= end; value += step) {
        result.pb(value);
    }
    return result;
}
} // namespace vv
