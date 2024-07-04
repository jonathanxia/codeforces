#pragma once
#include <lib/common.h>
namespace vv {
template <typename T>
bool any(const vector<T>& a)
{
    return std::any_of(a.begin(), a.end(), [](bool b) { return b; });
}
}