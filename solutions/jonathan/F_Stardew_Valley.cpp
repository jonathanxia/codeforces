#include<lib/common.h>
#include<lib/graph/eulerian_tour.h>

// Note that the link is https://codeforces.com/contest/1994/problem/F
// But we need to set up a checker for constructive problems

void solve() {
    ll n, m; cin >> n >> m;
    array<vvpl, 2> graph;
    graph[0].resize(n);
    graph[1].resize(n);
    vi odd_deg(n);
    FOR(i, 0, m - 1) {
        ll u, v; cin >> u >> v; u--; v--;
        ll c; cin >> c;
        graph[c][u].push_back({v, 1});
        if (c == 1) {
            odd_deg[u] += 1;
            odd_deg[v] += 1;
        }
        if (u != v) {
            graph[c][v].push_back({u, 1});
        }
    }

    walk(i, odd_deg) odd_deg[i] %= 2;
    // dbg(odd_deg);

    // Now just run a dfs I guess
    vb visited(n);
    vl num_odd_child(n);
    bool is_impossible = false;
    function<void(ll, ll)> dfs = [&](ll node, ll parent) {
        visited[node] = true;
        if (odd_deg[node]) {
            num_odd_child[node] = 1;
        }
        foreachp(child, w, graph[0][node]) {
            if (!visited[child]) {
                dfs(child, node);
                num_odd_child[node] += num_odd_child[child];
            }
        }
        // dbg(num_odd_child);
        chkmod(num_odd_child[node], 2);
        if (num_odd_child[node] == 1 && parent != -1) {
            // Add edge (node, parent)
            graph[1][node].push_back({parent, 1});
            graph[1][parent].push_back({node, 1});
        }
    };
    FOR(node, 0, n - 1) if (!visited[node]) {
        // dprint("Running dfs on node", node);
        dfs(node, -1);
        if (num_odd_child[node] == 1) is_impossible = true;
    }
    // dbg(num_odd_child);
    if (is_impossible) {
        print("NO"); return;
    }
    print("YES");
    vvi path = graph::findEulerianToursAndPaths(graph[1]);
    print(len(path[0]) - 1);
    print(LC(x + 1, x, path[0]));

}

int main() {
    init();
    int t; cin >> t;
    cep(t) solve();
    return 0;
}