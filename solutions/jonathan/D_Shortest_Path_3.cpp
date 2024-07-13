// Link: https://atcoder.jp/contests/abc362/tasks/abc362_d
#include <lib/graph/dijkstra.h>
#include <lib/vv/slc.h>
using namespace vv;

void solve() {
    ll n; cin >> n;
    vvpl graph(2 * n);
    ll m; cin >> m;
    vl a(n); cin >> a;
    FOR(i, 0, n - 1) {
        graph[2 * i].push_back({2 * i + 1, a[i]});
    }
    cepeat(m) {
        ll u, v, b; cin >> u >> v >> b; u--; v--;
        graph[2 * u + 1].push_back({2 * v, b});
        graph[2 * v + 1].push_back({2 * u, b});
    }
    vl dist(2 * n);
    graph::dijkstra(graph, dist, 0);
    vl output(n);
    FOR(i, 0, n - 1) {
        output[i] = dist[2 * i + 1];
    }
    print(slc(output, 1, n - 1));
}

int main() {
    init();
    solve();
    return 0;
}