#include <lib/lazy_segment_tree.h>

template <typename T, typename Node=node>
struct SegmentTree : LazySegmentTree<T, Node, lazynode> {
    SegmentTree(const vector<T>& v, function<node(node, node)> merge2)
        : LazySegmentTree(
            v, merge2, [](Node n1, int i, lazynode ln) {
            assert (i == 1);
            return Node(ln.data); },
            [](lazynode n1, lazynode n2) {
                return n2;
            })
    {
    }
};
