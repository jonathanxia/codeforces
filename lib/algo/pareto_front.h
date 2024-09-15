#pragma once
#include <lib/common.h>

/**
 * Computes the pareto front of the given points
 * 
 * Runtime: n log n
 */
template <typename T>
vector<pair<T, T>> pareto_front(vector<pair<T, T>> points) {
    sort(ALL(points));
    ll n = len(points);
    vector<pair<T, T>> result;
    if (n == 0) return result;
    result.push_back(points[n - 1]);
    DOR(i, n - 2, 0) {
        if (points[i].second > result.back().second) {
            result.push_back(points[i]);
        }
    }
    reverse(ALL(result));
    return result;
}