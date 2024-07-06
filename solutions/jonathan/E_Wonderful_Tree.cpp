// Link: https://codeforces.com/contest/1987/problem/E
#include<lib/dfs.h>
#include<lib/vv/sort.h>


void solve() {
    ll n; cin >> n;
    vl a(n); cin >> a;
    vvpl graph(n);

    FOR(i, 2, n) {
        ll u = i - 1;
        ll v; cin >> v;
        v--;
        graph[u].pb({v, 1});
        graph[v].pb({u, 1});
    }
    DfsTree tree(graph, 0);

    vl delta(n, -1e18);
    FOR(v, 0, n - 1) {
        ll num = 0;
        ll tot = 0;
        foreachp(child, w, graph[v]) {
            if (child == tree.parent[v]) continue;
            tot += a[child];
            num++;
        }
        if (num > 0) {
            delta[v] = a[v] - tot;
        }
    }
    ll ans = 0;
    function<void(ll, ll)> dfs = [&](ll node, ll parent) {
        ll num_child = 0;
        foreachp(child, w, graph[node]) {
            if (child == parent) continue;
            dfs(child, node);
            num_child++;
        }
        if (num_child == 0) return;

        if (delta[node] <= 0) return;
        // We have positive delta, so we need to flow it to some negative delta
        // Prioritize the close ones
        ll start = tree.node_to_counter[node];
        ll end = start + tree.num_desc[node] - 1;
        vpl candidates;
        FOR(c, start + 1, end) {
            ll v = tree.counter_to_node[c];
            if (delta[v] < 0) candidates.push_back({tree.height[v], v});
        }
        // Flow it flow it!
        vv::sort(candidates);
        ll idx = 0;
        while (delta[node] > 0) {
            auto [h, v] = candidates[idx];
            ll amt = -delta[v];
            amt = min(amt, delta[node]);
            delta[v] += amt;
            delta[node] -= amt;
            ans += amt * (h - tree.height[node]);
            idx++;
        }
    };
    dfs(0, -1);
    print(ans);
}

int main() {
    init();
    int t; cin >> t;
    cep(t) solve();
    return 0;
}