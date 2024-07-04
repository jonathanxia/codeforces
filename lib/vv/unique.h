#pragma once
#include <lib/common.h>

namespace vv {
template <typename T>
std::vector<T> unique(const std::vector<T>& input) {
    std::set<T> uniqueSet(input.begin(), input.end());
    std::vector<T> uniqueVector(uniqueSet.begin(), uniqueSet.end());
    return uniqueVector;
}
}