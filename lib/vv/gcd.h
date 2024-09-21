#pragma once
#include <lib/common.h>

namespace vv {
    template <typename T>
    T gcd(const vector<T>& a) {
        return std::accumulate(ALL(a), T(0), [](T x, T y) { return std::gcd(x, y); });
    }
}