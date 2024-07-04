#pragma once
#include <lib/common.h>

namespace vv {
/**
 * Inverts the permutation in p.
 * 
 * Returns an array a such that p[a[i]] = a[p[i]] = i
*/
template <typename T>
std::vector<T> invperm(const std::vector<T>& p) {
    vector<T> a(len(p));
    walk(i, p) {
        a[p[i]] = i;
    }
    return a;
}
}