#pragma once
template<typename T>
struct FenwickTree {
    vector<T> bit;  // binary indexed tree
    int n;

    FenwickTree(int n_) {
        this->n = n_;
        bit.assign(n_, 0);
    }

    FenwickTree(vector<T> const &a) : FenwickTree(a.size()){
        for (int i = 0; i < n; i++) {
            bit[i] += a[i];
            int r = i | (i + 1);
            if (r < n) bit[r] += bit[i];
        }
    }

    T sum(ll r) {
        if (r < 0) return T(0);
        if (r >= n) r = n - 1;
        T ret = 0;
        for (; r >= 0; r = (r & (r + 1)) - 1)
            ret += bit[r];
        return ret;
    }

    T sum(ll l, ll r) {
        if (l > r) return T(0);
        return sum(r) - sum(l - 1);
    }

    void add(int idx, T delta) {
        for (; idx < n; idx = idx | (idx + 1)) {
            bit[idx] += delta;
        }
    }

    void assign(int idx, T new_val) {
        T val = sum(idx, idx);
        add(idx, new_val - val);
    }
};

