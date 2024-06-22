#pragma once
#include <lib/common.h>

/**
 * A small array that has a notion of size so you can
 * do push_back but it will be backed by a static arr
 * 
 * Usage: https://codeforces.com/problemset/problem/1902/F
 */
template <typename T, int K>
struct small_array {
    int n;
    array<T, K> data;

    // Type aliases for iterator types
    using iterator = typename std::array<T, K>::iterator;
    using const_iterator = typename std::array<T, K>::const_iterator;

    // begin() and end() functions to support range-based for loops
    iterator begin() { return data.begin(); }
    const_iterator begin() const { return data.begin(); }
    iterator end() { return data.begin() + n; }
    const_iterator end() const { return data.begin() + n; }
    
    small_array() : n(0) {}
    const T& operator[](int idx) const { return data[idx]; }
    T& operator[](int idx) { return data[idx]; }

    friend ostream& operator<<(ostream& os, small_array arr) {
        os << "{ ";
        FOR(i, 0, arr.n - 1)  { os << arr.data[i] << " "; }
        os << "}";
        return os;
    }

    // Vector functions
    void push_back(T val) { data[n++] = val; }
    void pop_back() { n--; }
    T& back() { return data[n - 1]; }
    int size() { return n; }
};