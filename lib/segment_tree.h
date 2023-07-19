#include "common.h"

class SegmentTree {
public:
    struct node {
        ll mx;
        node() { mx = -1e9; }
        node(ll val) { mx = val; }
    };

    node temp;

    // MODIFY ME!
    node merge(node l, node r)
    {
        temp.mx = max(l.mx, r.mx);
        return temp;
    }

    ll n;
    vector<node> t;

    SegmentTree(ll sz)
        : t(2 * sz)
    {
        n = sz;
        repi(i, 0, n - 1) t[i + n] = node();
        dep(i, n - 1, 1)
        {
            t[i] = merge(t[i << 1], t[i << 1 | 1]);
        }
    }

    template <typename T>
    SegmentTree(const vector<T> a)
        : t(2 * a.size())
    {
        n = a.size();
        repi(i, 0, n - 1) t[i + n] = node(a[i]);
        dep(i, n - 1, 1)
        {
            t[i] = merge(t[i << 1], t[i << 1 | 1]);
        }
    }

    void modify(ll p, const node& value)
    {
        for (t[p += n] = value; p >>= 1;)
            t[p] = merge(t[p << 1], t[p << 1 | 1]);
    }

    node query(ll l, ll r)
    {
        node resl, resr;
        r++;
        for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
            if (l & 1)
                resl = merge(resl, t[l++]);
            if (r & 1)
                resr = merge(t[--r], resr);
        }

        return merge(resl, resr);
    }
};

// int main() {
//     vl a{1, 3, 4, 2, 5, 2};
//     SegmentTree segtree(a);
//     print("max(2, 4)=", segtree.query(2, 4).mx);
//     segtree.modify(4, 3);
//     print("max(2, 4)=", segtree.query(2, 4).mx);
//     print("max(0, 0)=", segtree.query(0, 0).mx);
//     return 0;
// }