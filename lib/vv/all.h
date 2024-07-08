#pragma once
#include <lib/common.h>
namespace vv {
template <typename T>
bool all(const vector<T>& a)
{
    return std::all_of(a.begin(), a.end(), [](bool b) { return b; });
}
}