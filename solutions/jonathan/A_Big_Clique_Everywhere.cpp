// Link: https://atcoder.jp/contests/agc067/tasks/agc067_a
#include <lib/graph/bipartite.h>
#include <lib/graph/complement.h>

void solve() {
    ll n, m; cin >> n >> m;
    vvpl graph(n);
    cepeat(m) {
        ll u, v; cin >> u >> v; u--; v--;
        graph[u].pb({v, 1});
        graph[v].pb({u, 1});
    }
    if (m < ceildiv(n, 2) * (ceildiv(n, 2) - 1) / 2) {
        print("No"); return;
    }

    vvpl g_prime = graph::complement(graph);
    vi color(n);
    if (graph::isBipartite(g_prime, color)) {
        print("Yes"); return;
    }
    else {
        print("No"); return;
    }
}

int main() {
    init();
    ll t; cin >> t;
    cepeat(t) solve();
    return 0;
}