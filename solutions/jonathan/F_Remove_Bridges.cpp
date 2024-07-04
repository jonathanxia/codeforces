// Link: https://codeforces.com/contest/1976/problem/F
#include <lib/dfs.h>
#include <atcoder/lazysegtree>

using S = pl;
S op(S l, S r) {
    return max(l, r);
}
S e() { return {-1e9, -1}; }
using F = ll;
S mapping(F l, S r) {
    if (!l) return r;
    return {l + r.first, r.second};
}
F composition(F l, F r) { return l + r; }
F id() { return 0; }
// atcoder::lazy_segtree<S, op, e, F, mapping, composition, id> seg(a);

void solve() {
    ll n; cin >> n;
    vvpl graph(n); inp::read_tree(graph);

    DfsTree tree(graph, 0);

    ll num_edges = n - 1;
    vl output(n - 1);
    vpl depths(n);
    FOR(node, 0, n - 1) {
        ll c = tree.node_to_counter[node];
        depths[c] = {tree.height[node], node};
    }

    atcoder::lazy_segtree<S, op, e, F, mapping, composition, id> seg(depths);

    FOR(k, 0, n - 2) {
        if (num_edges == 0) break;
        pl data = seg.query(0, n - 1);
        num_edges -= data.first;
        output[k] = num_edges;

        // update it now properly
        ll node = data.second;
        FOR(i, 0, data.first - 1) {
            ll start = tree.node_to_counter[node];
            ll end = start + tree.num_desc[node] - 1;
            seg.update(start, end, -1);
            node = tree.parent[node];
        }
    }

    vl ans(n - 1);
    ans[0] = output[0];
    SFOR(i, 2, n - 2, 2) {
        ans[i / 2] = output[i];
    }
    print(ans);
}

int main() {
    init();
    int t; cin >> t;
    cep(t) solve();
    return 0;
}