#pragma once

#include <lib/common.h>
#include <atcoder/lazysegtree>

/**
 * Defines a LazySegmentTree that supports:
 * 
 * update(l, r, v) -> assigns v to a[l ... r] = v
 * query(l, r) -> returns sum(a[l...r])
 */
namespace lazy_assign_sum {
    struct S {
        ll sm; // sum
        ll sz; // length of the interval
    };
    S op(S l, S r) {
        return {l.sm + r.sm, l.sz + r.sz};
    }
    S e() { return S{0, 1}; }

    using F = pl; // Value (to assign), bool active
    // So, the second entry being false means this lazy seg is not active
    S mapping(F l, S r) {
        if (!l.second) return r;
        return {r.sz * l.first, r.sz};
    }
    F composition(F l, F r) {
        if (l.second) return l;
        return r;
    }
    F id() { return {0, 0}; }

    using LazySegTree = atcoder::lazy_segtree<S, op, e, F, mapping, composition, id>;

    LazySegTree init(const vector<ll>& a) {
        vector<S> b(len(a));
        walk(i, b) {
            b[i] = S{a[i], 1LL};
        }
        return LazySegTree(b);
    }
} // namespace lazy_assign_sum
