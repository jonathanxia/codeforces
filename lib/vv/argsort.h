#pragma once
#include <lib/common.h>
namespace vv {
template <typename T>
vector<int> argsort(const vector<T>& a)
{
    // Initialize original index positions
    vector<int> indices(a.size());
    for (int i = 0; i < len(indices); ++i) {
        indices[i] = i;
    }

    // Sort the indices based on comparing array values
    std::stable_sort(indices.begin(), indices.end(), [&](int i1, int i2) { return a[i1] < a[i2]; });

    return indices;
}


}