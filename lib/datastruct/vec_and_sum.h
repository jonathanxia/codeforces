#pragma once
#include <lib/common.h>

template <typename T>
struct VectorAndSum {
    vector<T> values;
    T tot;
    VectorAndSum(int n) : values(n, 0), tot(0) {}
    VectorAndSum(const vector<T>& values) : values(values), tot(0) {
        for (const T& v : values) tot += v;
    }

    void push_back(T val) {
        values.push_back(val);
        tot += val;
    }

    void pop_back() {
        tot -= values.back();
        values.pop_back();
    }

    void assign(int idx, T val) {
        tot -= values[idx];
        values[idx] = val;
        tot += val;
    }

    T sum() const {
        return tot;
    }

    int size() const { return values.size(); }

    // Read-only: write through assign() so the sum stays in sync.
    const T& operator[](int idx) const {
        return values[idx];
    }

    // Printing
    friend std::ostream& operator<<(std::ostream& os, const VectorAndSum<T>& arr) {
        return os << "[" << arr.values << "](sum=" << arr.tot << ")";
    }
};
