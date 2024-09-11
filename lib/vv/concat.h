#pragma once

#include <lib/common.h>
namespace vv {
    template <typename T>
    vector<T> concat(const vector<T>& a, const vector<T>& b)
    {
        vector<T> ret(a);
        // Better constant factor anyway
        ret.reserve(len(a) + len(b));
        foreach(x, b) ret.push_back(x);
        return ret;
    }
}