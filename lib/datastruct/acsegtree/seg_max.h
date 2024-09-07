#pragma once

#include <lib/common.h>
#include <atcoder/segtree>

/**
 * Defines a SegmentTree that supports:
 * 
 * query(l, r) -> returns max(a[l...r])
 */
namespace seg_max {
    using S=ll;
    S op(S a, S b) { return max(a, b); }
    S e() { return -1e18; }

    using SegTree = atcoder::segtree<S, op, e>;
}
