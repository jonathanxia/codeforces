// Link: https://codeforces.com/contest/2002/problem/D2
#include<lib/common.h>
#include<lib/vv/counter.h>
#include<lib/vv/sort.h>
#include<lib/vv/invperm.h>
#include<lib/tree/lca_tree.h>
#include <lib/datastruct/vec_and_sum.h>

using namespace vv;

void solve() {
    ll n, q; cin >> n >> q;
    vvpl graph(n);
    FOR(i, 2, n) {
        ll par; cin >> par;
        // the edge is i -> par
        graph[i - 1].pb({par - 1, 1});
        graph[par - 1].pb({i - 1, 1});
    }
    DfsTree tree(graph, 0);
    LCATree lca_tree(tree);
    vl p(n); cin >> p; p = LC(x - 1, x, p);

    VectorAndSum<ll> is_good(n);
    // We say index i is good when p[i], p[i + 1]
    // is good.
    // i.e., parent(p[i + 1]) is the LCA, or p[i] is the parent of p[i + 1]
    auto check_good = [&](ll i) {
        if (p[i] == tree.parent[p[i + 1]] || lca_tree.lca(p[i], p[i + 1]) == tree.parent[p[i + 1]]) {
            is_good.assign(i, 1);
        }
        else {
            is_good.assign(i, 0);
        }
    };
    FOR(i, 0, n - 2) {
        check_good(i);
    }
    cepeat(q) {
        ll x, y; cin >> x >> y; x--; y--;
        swap(p[x], p[y]);
        set<ll> indices {x - 1, x, y - 1, y};
        foreach(idx, indices) {
            if (ordered(0, idx, n - 2)) check_good(idx);
        }
        print(is_good.sum() == n - 1 ? "YES" : "NO");
    }
}

int main() {
    init();
    int t; cin >> t;
    cep(t) solve();
    return 0;
}