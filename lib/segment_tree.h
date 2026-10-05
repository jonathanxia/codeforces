#pragma once
#include <lib/lazy_segment_tree.h>

// Point-update segment tree: only call update(i, i, val), which assigns val
template <typename T, typename Node=node>
struct SegmentTree : LazySegmentTree<T, Node, lazynode> {
    SegmentTree(const vector<T>& v, function<Node(Node, Node)> merge2)
        : LazySegmentTree<T, Node, lazynode>(
            v, merge2, [](Node, int i, lazynode ln) {
            assert (i == 1);
            return Node(ln.data); },
            [](lazynode, lazynode n2) {
                return n2;
            })
    {
    }
};
