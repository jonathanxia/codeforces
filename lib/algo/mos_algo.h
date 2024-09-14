#pragma once
#include <lib/common.h>

/**
 * This implements Mo's algorithm. To use this, you construct
 * a bunch of Query objects that store [left, right] queries.
 * The Query objects are endowed with a comparator that allows
 * you to sort the Query objects if they are in some vector.
 * 
 * You can then iterate through the queries in Mo fashion. We use
 * Hilbert curves for the ordering: https://codeforces.com/blog/entry/61203
 */

// Example usage:
/*
    vector<Query> queries(q);
    vl output(q);
    FOR(idx, 0, q - 1) {
        ll l, r; cin >> l >> r; l--; r--;
        queries[idx] = Query(l, r, idx);
    }
    sort(queries);

    ll left = 0;
    ll right = -1;
    auto func = [&](ll val, ll delta) { // ... };

    foreach(query, queries) {
        // Do expansions first
        while (right < query.right) {
            right++;
            func(b[right], 1);
        }
        while (left > query.left) {
            left--;
            func(b[left], 1);
        }
        // Then contractions
        while (right > query.right) {
            func(b[right], -1);
            right--;
        }
        while (left < query.left) {
            func(b[left], -1);
            left++;
        }

        // Query the datastructure
        output[query.idx] = calc_ans(...);
    }
*/

namespace mos_algo {
    inline int64_t gilbertOrder(int x, int y, int pow, int rotate) {
        if (pow == 0) {
            return 0;
        }
        int hpow = 1 << (pow-1);
        int seg = (x < hpow) ? (
            (y < hpow) ? 0 : 3
        ) : (
            (y < hpow) ? 1 : 2
        );
        seg = (seg + rotate) & 3;
        const int rotateDelta[4] = {3, 0, 0, 1};
        int nx = x & (x ^ hpow), ny = y & (y ^ hpow);
        int nrot = (rotate + rotateDelta[seg]) & 3;
        int64_t subSquareSize = int64_t(1) << (2*pow - 2);
        int64_t ans = seg * subSquareSize;
        int64_t add = gilbertOrder(nx, ny, pow-1, nrot);
        ans += (seg == 1 || seg == 2) ? add : (subSquareSize - add - 1);
        return ans;
    }

    /**
     * LG_N = upper bound on log2(n), where l, r <= n
     * Typically problems with n <= 10**6, suffices to use 21
     */
    template <int LG_N=21>
    struct Query {
        int left, right, idx;
        int64_t ord;

        Query() : left(-1), right(-1), idx(-1), ord(-1) {}

        Query(int l_, int r_, int idx_) : left(l_), right(r_), idx(idx_) {
            this->calcOrder();
        }

        inline void calcOrder() {
            this->ord = gilbertOrder(this->left, this->right, LG_N, 0);
        }
    };

    template <int LG_N=21>
    inline bool operator<(const Query<LG_N> &a, const Query<LG_N> &b) {
        return a.ord < b.ord;
    }
} // namespace mos_algo

using Query=mos_algo::Query<21>;
