#pragma once
#include <lib/common.h>

struct node {
    ll data;
    bool is_empty;

    node()
    {
        data = 0;
        is_empty = true;
    }
    node(ll val)
    {
        data = val;
        is_empty = false;
    }
};

struct lazynode {
    ll data;
    bool is_empty;

    lazynode()
    {
        data = 0;
        is_empty = true;
    }
    lazynode(ll val)
    {
        data = val;
        is_empty = false;
    }
};

std::ostream& operator<<(std::ostream& os, const node& mp)
{
    os << mp.data;
    return os;
}

std::ostream& operator<<(std::ostream& os, const lazynode& mp)
{
    os << mp.data;
    return os;
}

template <typename T, typename Node=node, typename LazyNode=lazynode>
struct LazySegmentTree {
public:
    ll n;
    vector<T> a;
    function<Node(Node, Node)> merge;
    function<Node(Node, int, LazyNode)> apply;
    function<LazyNode(LazyNode, LazyNode)> lazymerge;

    vector<LazyNode> lazy;
    vector<Node> tr;

    Node truemerge(Node Node1, Node Node2)
    {
        if (Node1.is_empty) {
            return Node2;
        }
        if (Node2.is_empty) {
            return Node1;
        }
        return merge(Node1, Node2);
    }

    Node trueapply(Node Node1, int num, LazyNode Node2)
    {
        if (Node2.is_empty) {
            return Node1;
        }
        return apply(Node1, num, Node2);
    }

    LazyNode truelazymerge(LazyNode Node1, LazyNode Node2)
    {
        if (Node2.is_empty) {
            return Node1;
        }
        if (Node1.is_empty) {
            return Node2;
        }
        return lazymerge(Node1, Node2);
    }

    void push(int l, int r, int idx)
    {
        if (!lazy[idx].is_empty) {
            tr[idx] = trueapply(tr[idx], r - l + 1, lazy[idx]);

            if (l != r) {
                lazy[2 * idx + 1] = truelazymerge(lazy[2 * idx + 1], lazy[idx]);
                lazy[2 * idx + 2] = truelazymerge(lazy[2 * idx + 2], lazy[idx]);
            }

            lazy[idx] = LazyNode();
        }
    }

    void init(int l, int r, int idx)
    {
        if (l == r) {
            tr[idx] = Node(a[l]);
            return;
        }

        int mid = (l + r) >> 1;
        init(l, mid, 2 * idx + 1);
        init(mid + 1, r, 2 * idx + 2);

        tr[idx] = truemerge(tr[2 * idx + 1], tr[2 * idx + 2]);
    }

    LazySegmentTree(
        const vector<T>& arr,
        function<Node(Node, Node)> op,
        function<Node(Node, int, LazyNode)> applyop,
        function<LazyNode(LazyNode, LazyNode)> lazyop

        )
        : a(arr)
        , lazy(4 * arr.size())
        , tr(4 * arr.size())
    {
        merge = op;
        apply = applyop;
        lazymerge = lazyop;
        n = a.size();
        init(0, n - 1, 0);
    }

    void update(int qL, int qR, ll val, int l, int r, int idx)
    {
        push(l, r, idx);

        if (qL > r || l > qR) {
            return;
        }

        if (qL <= l && r <= qR) {
            lazy[idx] = truelazymerge(lazy[idx], LazyNode(val));
            push(l, r, idx);
            return;
        }

        int mid = (l + r) >> 1;
        update(qL, qR, val, l, mid, 2 * idx + 1);
        update(qL, qR, val, mid + 1, r, 2 * idx + 2);

        tr[idx] = truemerge(tr[2 * idx + 1], tr[2 * idx + 2]);
    }

    void update(int qL, int qR, ll val)
    {
        update(qL, qR, val, 0, n - 1, 0);
    }

    Node query(int qL, int qR, int l, int r, int idx)
    {
        push(l, r, idx);

        if (l > qR || r < qL) {
            return Node();
        }

        if (qL <= l && r <= qR) {
            return tr[idx];
        }

        int mid = (l + r) >> 1;
        return truemerge(query(qL, qR, l, mid, 2 * idx + 1), query(qL, qR, mid + 1, r, 2 * idx + 2));
    }

    // Inclusive query
    Node query(int qL, int qR)
    {
        return query(qL, qR, 0, n - 1, 0);
    }
};

// template <typename T>
// struct MinSegmentTree : public LazySegmentTree<T> {
// public:
//     MinSegmentTree(const vector<T>& v) : LazySegmentTree<T>(
//         v,
//         [](node n1, node n2) {
//             return node(min(n1.data, n2.data));
//         },
//         [](node n1, int num, lazynode n2) {
//             // Assuming assignment updates
//             return node(n2.data);
//         },
//         [](lazynode n1, lazynode n2) {
//             return lazynode(n2.data);
//         }
//     )
//     {}
// };

// template <typename T>
// struct MaxSegmentTree : public LazySegmentTree<T> {
// public:
//     MaxSegmentTree(const vector<T>& v) : LazySegmentTree<T>(
//         v,
//         [](node n1, node n2) {
//             return node(max(n1.data, n2.data));
//         },
//         [](node n1, int num, lazynode n2) {
//             // Assuming assignment updates
//             return node(n2.data);
//         },
//         [](lazynode n1, lazynode n2) {
//             return lazynode(n2.data);
//         }
//     )
//     {}
// };

// template <typename T>
// struct SumSegmentTree : public LazySegmentTree<T> {
// public:
//     SumSegmentTree(const vector<T>& v) : LazySegmentTree<T>(
//         v,
//         [](node n1, node n2) {
//             return node(n1.data + n2.data);
//         },
//         [](node n1, int num, lazynode n2) {
//             // Assuming assignment updates
//             return node(n2.data * num);
//         },
//         [](lazynode n1, lazynode n2) {
//             return lazynode(n2.data);
//         }
//     )
//     {}
// };
