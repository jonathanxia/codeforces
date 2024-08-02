#pragma once

#include <lib/common.h>
#include <atcoder/lazysegtree>

/**
 * Defines a LazySegmentTree that supports:
 * 
 * update(l, r, v) -> adds +v to everything from [l, r]
 * query(l, r) -> returns min on a[l, r] and how many times it shows up
 */

namespace lazy_sum_min_count {
    using S=pl; // Value, count
    S op(S l, S r) {
        if (l.first < r.first) return l;
        if (l.first > r.first) return r;
        return S{l.first, l.second + r.second};
    }
    S e() { return S{1e18, 0}; }

    using F=ll;
    S mapping(F l, S r) {
        if (!l) return r;
        return S{r.first + l, r.second};
    }
    F composition(F l, F r) { return l + r; }
    F id() { return 0; }

    using LazySegTree = atcoder::lazy_segtree<S, op, e, F, mapping, composition, id>;

    LazySegTree init(const vector<ll>& a) {
        vector<pl> b = LC(mp(x, 1LL), x, a);
        return LazySegTree(b);
    }
}
