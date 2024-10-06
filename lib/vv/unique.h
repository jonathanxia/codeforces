#pragma once
#include <lib/common.h>

namespace vv {
template <typename T>
std::vector<T> unique(const std::vector<T>& input) {
    std::set<T> uniqueSet(input.begin(), input.end());
    std::vector<T> uniqueVector(uniqueSet.begin(), uniqueSet.end());
    return uniqueVector;
}

// Keeps deduped items in the same order in which they appear in input
// ie. if the first copy of T1 is before the first copy of T2 in input,
// then T1 will be before T2 in the output
template <typename T>
std::vector<T> stable_unique(const std::vector<T>& input) {
    std::vector<T> ans;
    uset<T> already_found;
    foreach (item, input) {
        if (already_found.count(item)) {
            continue;
        } else {
            ans.pb(item);
            already_found.insert(item);
        }
    }
    return ans;
}
}