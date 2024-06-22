#pragma once
#include <lib/common.h>

/**
 * Maintains a basis in XOR space. Given a bunch of integers
 * a[0], a[1], ..., a[n], query what sorts of numbers
 * can be expressed as an XOR of some subset.
*/
template<class T, int max_log=31>
struct XORBasis {
    array<T, max_log> base;

    XORBasis() {
        init();
    }
 
    void init() {
        base.fill(0);
    }
 
    void add(T val) {
        for(int i = max_log - 1; i >= 0; i--) {
            if((val >> i) & 1) {
                if(!base[i]) {
                    base[i] = val;
                    return;
                } else {
                    val ^= base[i];
                }
            }
        }
    }
 
    inline int size() const {
        int sz = 0;
        for(int i = 0; i < max_log; i++) {
            sz += (bool)(base[i]);
        }
        return sz;
    }
 
    T max_xor() const {
        T res = 0;
        for(int i = max_log - 1; i >= 0; i--) {
            if(!((res >> i) & 1) && base[i]) {
                res ^= base[i];
            }
        }
 
        return res;
    }
 
    bool can_create(T val) const {
        for(int i = max_log - 1; i >= 0; i--) {
            if(((val >> i) & 1) && base[i]) {
                val ^= base[i];
            }
        }
 
        return (val == 0);
    }
 
    vector<T> get_basis() const {
        vector<T> res;
        for(int i = 0; i < max_log; i++) {
            if(base[i]) {
                res.push_back(base[i]);
            }
        }
        return res;
    }
 
    XORBasis<T> merge(XORBasis<T> other) const {
        if(max_log < other.max_log) {
            return other.merge(*this);
        }
 
        XORBasis<T> res = *this;
        for(auto x: other.base) {
            if(x) {
                res.add(x);
            }
        }
        return res;
    }

    friend ostream& operator<<(ostream& os, const XORBasis x) {
        os << "XORBasis{";
        os << x.get_basis() << "}";
        return os;
    }
};
 