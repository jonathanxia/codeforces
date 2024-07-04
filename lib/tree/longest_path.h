#pragma once
#include <lib/common.h>

// Only works for trees!
pair<ll, vl> longest_path(vvpl &graph, ll n)
{
    vl dist(n);
    vl parents(n);
    pl farthest = {0, 0};
    function<void(ll, ll)> dfs = [&](ll node, ll parent) -> void
    {
        chkmax(farthest, mp(dist[node], node));
        foreachp (child, weight, graph[node])
        {
            if (child == parent)
                continue;
            dist[child] = dist[node] + weight;
            parents[child] = node;
            dfs(child, node);
        }
    };
    dfs(0, -1);
    ll start = farthest.second;
    farthest = {0, 0};
    FOR(i, 0, n - 1) dist[i] = 0;
    FOR(i, 0, n - 1) parents[i] = 0;

    dfs(start, -1);
    parents[start] = -1;
    ll end = farthest.second;
    vl path;
    while (end != -1)
    {
        path.pb(end);
        end = parents[end];
    }

    return {dist[farthest.second], path};
}

