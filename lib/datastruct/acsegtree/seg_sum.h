#pragma once

#include <lib/common.h>
#include <atcoder/segtree>

/**
 * Defines a SegmentTree that supports:
 * 
 * query(l, r) -> returns sum(a[l...r])
 */
namespace seg_sum {
    using S=ll;
    S op(S a, S b) { return a + b; }
    S e() { return 0; }

    using SegTree = atcoder::segtree<S, op, e>;
}
