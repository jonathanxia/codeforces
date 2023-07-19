#include <lib/lazy_segment_tree.h>

struct SegmentTree : LazySegmentTree {
    template <typename T>
    SegmentTree(const vector<T>& v, function<node(node, node)> merge2)
        : LazySegmentTree(
            v, merge2, [](node n1, int i, lazynode ln) {
            assert (i == 1);
            return node(ln.data); },
            [](lazynode n1, lazynode n2) {
                return n2;
            })
    {
    }
};
