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

    T sum(int r) {
        T ret = 0;
        for (; r >= 0; r = (r & (r + 1)) - 1)
            ret += bit[r];
        return ret % 2;
    }

    T sum(int l, int r) {
        return sum(r) - sum(l - 1);
    }

    void add(int idx, T delta) {
        for (; idx < n; idx = idx | (idx + 1)) {
            bit[idx] += delta;
            bit[idx] %= 2;
        }
    }
};

