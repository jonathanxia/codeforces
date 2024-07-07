#pragma once
#include <lib/common.h>

template <typename T>
std::vector<int> longest_increasing_subsequence(const std::vector<T>& arr) {
    if (arr.empty()) return {};
    ll n = len(arr);
    
    // tails[i] = smallest possible last value for subsequence of length i + 1
    std::vector<T> tails;
    std::vector<int> indices(n);
    std::vector<int> prev(n, -1);

    for (int i = 0; i < n; ++i) {
        ll pos_in_tails;
        if (len(tails) > 0)
            pos_in_tails = smallest_st(pos, tails[pos] >= arr[i], 0, len(tails) - 1);
        else
            pos_in_tails = 0;

        if (pos_in_tails == len(tails)) {
            tails.push_back(arr[i]);
        }
        else {
            tails[pos_in_tails] = arr[i];
        }

        indices[pos_in_tails] = i;

        if (pos_in_tails > 0) {
            prev[i] = indices[pos_in_tails - 1];
        }
    }

    // Now it is just answer extraction
    std::vector<int> result;
    for (int i = indices[len(tails) - 1]; i >= 0; i = prev[i]) {
        result.push_back(i);
    }
    std::reverse(result.begin(), result.end());

    return result;
}
