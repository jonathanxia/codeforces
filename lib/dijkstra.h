#include <lib/common.h>
#include <lib/vv.h>

void dijkstra(ll n, const vvpl& graph, vl& dist, ll start, ll target) {
    // Run dijkstra on the graph
    vv::fill(dist, LONG_LONG_MAX);

    set<pl> pq;

    pq.insert({0, start});
    dist[start] = 0;
    while (!pq.empty()) {
        auto [distance, node] = mset::min(pq);
        pq.erase({distance, node});

        if (node == target) {
            break;
        }

        foreachp(child, edge, graph[node]) {
            if (distance + edge < dist[child]) {
                pq.erase({dist[child], child});
                pq.insert({distance + edge, child});
                dist[child] = distance + edge;
            }
        }
    }
}
