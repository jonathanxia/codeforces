#pragma once
#include <lib/common.h>
/**
 * A segment tree that allows range updates, but does not push down those updates.
 * 
 * Each node of the segment tree corresponds to an interval [L, R], and stores data
 * about it in Node. It can accept an UpdateNode object which will update the Node data, but
 * not push down.
 * 
 * We can also query an index Q, and the segtree will walk through all nodes that cover
 * Q, and apply custom combine_query() calls.
 * 
 * Usage: https://atcoder.jp/contests/abc342/submissions/50627405
 * 
using Node=set<pl>;
using UpdateNode = pl;

void update_op(Node& node, UpdateNode u) {
    if (u.first > 0)
        node.insert(u);
    else
        node.erase({-u.first, u.second});
}

using QueryType = ll;
QueryType extract_query(Node& node) {
    if (len(node)) {
        return node.rbegin()->first;
    }
    else {
        return -1e18;
    }
}

QueryType combine_query(QueryType q1, QueryType q2) {
    return max(q1, q2);
}

QueryType e() { return -1e18; }

void solve() {
    ll n; cin >> n;
    vector<set<pl>> a(n);
    FOR(i, 0, n - 1) {
        ll v; cin >> v;
        a[i].insert(pl{v, -1LL});
    }

    PointQuerySegmentTree<Node, UpdateNode, update_op, QueryType, extract_query,
                          combine_query, e> seg(a);
    ll q; cin >> q;

    ll cnt = 1;
    vector<array3> updates(q + 1);
    cepeat(q) {
        ll typ; cin >> typ;
        if (typ == 1) {
            ll L, R, X; cin >> L >> R >> X; L--; R--;
            seg.update(L, R, pl{X, cnt});
            updates[cnt] = {L, R, X};
        }
        else if (typ == 2) {
            ll i; cin >> i;
            seg.update(updates[i][0], updates[i][1], pl{-updates[i][2], i});
        }
        else {
            ll i; cin >> i; i--;
            print(seg.query(i, i));
        }
        cnt++;
    }
}
*/
template <typename Node, typename UpdateNode, void (*update_op)(Node&, UpdateNode),
          typename QueryType, QueryType (*extract_query)(Node&),
          QueryType (*combine_query)(QueryType, QueryType),
          QueryType (*e)()>
struct PointQuerySegmentTree {
    ll n;
    vector<Node> tr;

    PointQuerySegmentTree(const vector<Node>& arr) : n(len(arr)), tr(4 * n) {
        init(arr, 0, 0, n - 1);
    }

    void init(const vector<Node>& arr, int idx, int left, int right) {
        if (left == right) {
            tr[idx] = arr[left];
            return;
        }
        int mid = (left + right) / 2;
        init(arr, 2 * idx + 1, left, mid);
        init(arr, 2 * idx + 2, mid + 1, right);
    }

    void update(int idx, int l, int r, int qL, int qR, UpdateNode update_node) {
        if (qL > r || l > qR) {
            return;
        }

        // Within the query segment now
        if (qL <= l && r <= qR) {
            update_op(tr[idx], update_node);
            return;
        }

        int mid = (l + r) >> 1;
        update(2 * idx + 1, l, mid, qL, qR, update_node);
        update(2 * idx + 2, mid + 1, r, qL, qR, update_node);
    }

    void update(int q_left, int q_right, UpdateNode update_node) {
        update(0, 0, n - 1, q_left, q_right, update_node);
    }

    QueryType query(int qL, int qR, int l, int r, int idx)
    {
        if (l > qR || r < qL) {
            return e();
        }

        if (qL <= l && r <= qR) {
            return extract_query(tr[idx]);
        }

        int mid = (l + r) >> 1;
        QueryType c = combine_query(
            query(qL, qR, l, mid, 2 * idx + 1),
            query(qL, qR, mid + 1, r, 2 * idx + 2)
        );

        return combine_query(extract_query(tr[idx]), c);
    }

    // Inclusive query
    QueryType query(int qL, int qR)
    {
        return query(qL, qR, 0, n - 1, 0);
    }
};

