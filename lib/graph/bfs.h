#pragma once
#include <lib/common.h>

namespace graph {
    // Runs bfs on a graph and stores the distances in dist
    // Starts need to be passed in, can have multiple start points
    vl bfs(const vvl& graph, const vl& starts, ll default_dist = LLONG_MAX) {
        ll n = len(graph);
        vl dist(n);
        FOR(i, 0, n - 1) dist[i] = -1;

        deque<ll> pq;
        foreach(s, starts) {
            pq.push_back(s);
            dist[s] = 0;
        }

        while(len(pq)) {
            ll node = pq.front();
            pq.pop_front();

            // Process the node by adding its children
            foreach(child, graph[node]) {
                if (dist[child] >= 0) continue;

                dist[child] = dist[node] + 1;
                pq.push_back(child);
            }
        }
        return LC(x < 0 ? default_dist : x, x, dist);
    }
} // namespace graph