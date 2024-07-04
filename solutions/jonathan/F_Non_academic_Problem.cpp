// Link: https://codeforces.com/contest/1986/problem/F
#include <lib/graph/bridges.h>
#include <lib/dfs.h>

void solve() {
    ll n, m; cin >> n >> m;
    vvpl graph(n);
    cepeat(m) {
        ll u, v; cin >> u >> v; u--; v--;
        graph[u].pb({v, 1});
        graph[v].pb({u, 1});
    }
    vpl bridges = graph::find_bridges(graph);
    dbg(bridges);

    // get the tree
    DfsTree tree(graph, 0);
    ll ans = n * (n - 1) / 2;
    foreachp(u, v, bridges) {
        if (tree.height[u] > tree.height[v]) {
            swap(u, v);
        }

        ll k = tree.num_desc[v];
        ll j = n - k;
        if (chkmin(ans, k * (k - 1) / 2 + j * (j - 1) / 2)) dprint("Splitting edge", u + 1, v + 1);
    }
    print(ans);
}

int main() {
    init();
    int t; cin >> t;
    cep(t) solve();
    return 0;
}