#pragma once
#include <lib/common.h>

/**
 * Maintains a basis in XOR space. Given a bunch of integers
 * a[0], a[1], ..., a[n], query what sorts of numbers
 * can be expressed as an XOR of some subset.
 * 
 * Source: neal
*/
template<typename T, int BITS=30>
struct XORBasis {
    // A list of basis values sorted in decreasing order, where each value has a unique highest bit.
    // We use a static array instead of a vector for better performance.
    array<T, BITS> basis;
    int n = 0;
 
    T min_value(T start) const {
        if (n == BITS)
            return 0;
 
        for (int i = 0; i < n; i++)
            start = min(start, start ^ basis[i]);
 
        return start;
    }
 
    T max_value(T start = 0) const {
        if (n == BITS)
            return (T(1) << BITS) - 1;
 
        for (int i = 0; i < n; i++)
            start = max(start, start ^ basis[i]);
 
        return start;
    }
 
    bool add(T x) {
        x = min_value(x);
 
        if (x == 0)
            return false;
 
        basis[n++] = x;
        int k = n - 1;
 
        // Insertion sort.
        while (k > 0 && basis[k] > basis[k - 1]) {
            swap(basis[k], basis[k - 1]);
            k--;
        }
 
        // Optional: remove the highest bit of x from other basis elements.
        // for (int i = k - 1; i >= 0; i--)
        //     basis[i] = min(basis[i], basis[i] ^ x);
 
        return true;
    }

    void init() {
        FOR(i, 0, n - 1) basis[i] = 0;
        n = 0;
    }

    XORBasis() { init(); }
    int size() { return n; }

    bool can_create(T x) { return min_value(x) == 0; }
 
    void merge(const XORBasis<T, BITS> &other) {
        for (int i = 0; i < other.n && n < BITS; i++)
            add(other.basis[i]);
    }
 
    void merge(const XORBasis<T, BITS> &a, const XORBasis<T, BITS> &b) {
        if (a.n > b.n) {
            *this = a;
            merge(b);
        } else {
            *this = b;
            merge(a);
        }
    }

    friend ostream& operator<<(ostream& os, const XORBasis& p) {
        os << "XORBasis{ ";
        FOR(i, 0, p.n - 1) {
            os << p.basis[i] << " ";
        }
        os << "}";
        return os;
    }
};