#include <lib/common.h>

void dijkstra(ll n, const vvpl& graph, vl& dist, ll start, ll target) {
    // Run dijkstra on the graph
    vv::fill(dist, LONG_LONG_MAX);

    vb processed(n);
    set<pl> pq;

    pq.insert({start, 0});
    while (!pq.empty()) {
        auto [distance, node] = mset::min(pq);
        pq.erase({distance, node});

        if (processed[node]) continue;
        processed[node] = true;

        dist[node] = distance;
        if (node == target) {
            break;
        }

        foreachp(child, edge, graph[node]) {
            if (processed[child]) continue;
            pq.insert({distance + edge, child});
        }
    }
}