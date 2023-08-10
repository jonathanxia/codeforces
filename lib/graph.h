#include <lib/vv.h>

vl longest_path(vvl& graph, ll n) {
    vl dist(n);
    vl parents(n);
    pl farthest = {0, 0};
    function<void(ll, ll)> dfs = [&](ll node, ll parent) -> void {
        chkmax(farthest, mp(dist[node], node));
        foreach(child, graph[node]) {
            if (child == parent) continue;
            dist[child] = dist[node] + 1;
            parents[child] = node;
            dfs(child, node);
        }
    };
    dfs(0, -1);
    ll start = farthest.second;
    farthest = {0, 0};
    fill(dist, 0);
    fill(parents, 0);

    dfs(start, -1);
    parents[start] = -1;
    ll end = farthest.second;
    vl path;
    while (end != -1) {
        path.pb(end);
        end = parents[end];
    }

    return path;
}