#pragma once
#include <lib/common.h>

template <typename T>
struct VectorAndSum {
    vector<T> values;
    T tot;
    VectorAndSum(int n) : values(n, 0), tot(0) {}

    void push_back(T val) {
        values.push_back(val);
        tot += val;
    }

    void assign(int idx, T val) {
        tot -= values[idx];
        values[idx] = val;
        tot += val;
    }

    T sum() const {
        return tot;
    }

    T size() const { return values.size(); }

    T& operator[](int idx) {
        return this->values[idx];
    }
};
