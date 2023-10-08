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

struct LazySegmentTree {
public:
    ll n;
    vl a;
    function<node(node, node)> merge;
    function<node(node, int, lazynode)> apply;
    function<lazynode(lazynode, lazynode)> lazymerge;

    vector<lazynode> lazy;
    vector<node> tr;

    node truemerge(node node1, node node2)
    {
        if (node1.is_empty) {
            return node2;
        }
        if (node2.is_empty) {
            return node1;
        }
        return merge(node1, node2);
    }

    node trueapply(node node1, int num, lazynode node2)
    {
        if (node2.is_empty) {
            return node1;
        }
        return apply(node1, num, node2);
    }

    lazynode truelazymerge(lazynode node1, lazynode node2)
    {
        if (node2.is_empty) {
            return node1;
        }
        if (node1.is_empty) {
            return node2;
        }
        return lazymerge(node1, node2);
    }

    void push(int l, int r, int idx)
    {
        if (!lazy[idx].is_empty) {
            tr[idx] = trueapply(tr[idx], r - l + 1, lazy[idx]);

            if (l != r) {
                lazy[2 * idx + 1] = truelazymerge(lazy[2 * idx + 1], lazy[idx]);
                lazy[2 * idx + 2] = truelazymerge(lazy[2 * idx + 2], lazy[idx]);
            }

            lazy[idx] = lazynode();
        }
    }

    void init(int l, int r, int idx)
    {
        if (l == r) {
            tr[idx] = node(a[l]);
            return;
        }

        int mid = (l + r) >> 1;
        init(l, mid, 2 * idx + 1);
        init(mid + 1, r, 2 * idx + 2);

        tr[idx] = truemerge(tr[2 * idx + 1], tr[2 * idx + 2]);
    }

    template <typename T>
    LazySegmentTree(
        const vector<T>& arr,
        function<node(node, node)> op,
        function<node(node, int, lazynode)> applyop,
        function<lazynode(lazynode, lazynode)> lazyop

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
            lazy[idx] = truelazymerge(lazy[idx], lazynode(val));
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

    node query(int qL, int qR, int l, int r, int idx)
    {
        push(l, r, idx);

        if (l > qR || r < qL) {
            return node();
        }

        if (qL <= l && r <= qR) {
            return tr[idx];
        }

        int mid = (l + r) >> 1;
        return truemerge(query(qL, qR, l, mid, 2 * idx + 1), query(qL, qR, mid + 1, r, 2 * idx + 2));
    }

    // Inclusive query
    node query(int qL, int qR)
    {
        return query(qL, qR, 0, n - 1, 0);
    }
};

// struct MinSegmentTree : public LazySegmentTree {
// public:
//     template <typename T>
//     MinSegmentTree(const vector<T>& v) : LazySegmentTree(
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

// struct MaxSegmentTree : public LazySegmentTree {
// public:
//     template <typename T>
//     MaxSegmentTree(const vector<T>& v) : LazySegmentTree(
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

// struct SumSegmentTree : public LazySegmentTree {
// public:
//     template <typename T>
//     SumSegmentTree(const vector<T>& v) : LazySegmentTree(
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