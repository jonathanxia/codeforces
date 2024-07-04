#pragma once
#include <lib/common.h>
namespace vv {

template <typename T, typename S>
void push_front(vector<T>& a, S val) {
    a.insert(a.begin(), T(val));
}


}