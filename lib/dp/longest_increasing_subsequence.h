#pragma once
#include <lib/common.h>

template <typename T>
std::vector<int> longest_increasing_subsequence(const std::vector<T>& arr, bool strictly=true) {
    if (arr.empty()) return {};
    
    std::vector<T> tails;
    std::vector<int> indices(arr.size());
    std::vector<int> prev(arr.size(), -1);

    for (size_t i = 0; i < arr.size(); ++i) {
        auto it = (strictly) ? std::lower_bound(tails.begin(), tails.end(), arr[i]) 
                             : std::upper_bound(tails.begin(), tails.end(), arr[i]);

        int pos = std::distance(tails.begin(), it);
        if (it == tails.end()) {
            tails.push_back(arr[i]);
        } else {
            *it = arr[i];
        }

        indices[pos] = i;
        if (pos > 0) {
            prev[i] = indices[pos - 1];
        }
    }

    std::vector<int> result;
    for (int i = indices[len(tails) - 1]; i >= 0; i = prev[i]) {
        result.push_back(i);
    }
    std::reverse(result.begin(), result.end());

    return result;
}
