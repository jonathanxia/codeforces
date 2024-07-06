// Link: https://atcoder.jp/contests/abc361/tasks/abc361_e
#include<lib/common.h>
#include<lib/tree/longest_path.h>

void solve() {
    ll n; cin >> n;

    vvpl graph(n);
    ll tot = 0;
    FOR(i, 0, n - 2) {
        ll u, v, w; cin >> u >> v >> w;
        u--; v--;
        graph[u].push_back({v, w});
        graph[v].push_back({u, w});
        tot += w;
    }

    auto result = longest_path(graph, n);
    print(2 * tot - result.first);

}

int main() {
    init();
    solve();
    return 0;
}