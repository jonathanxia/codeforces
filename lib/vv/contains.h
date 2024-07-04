#pragma once
#include <lib/common.h>

namespace vv {
template <typename T>
bool contains(const vector<T>& vec, const T& value)
{
    auto it = std::find(vec.begin(), vec.end(), value);
    return (it != vec.end());
}
} // namespace vv