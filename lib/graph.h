#include "common.h"

// Specify target to stop Dijkstra once target is processed (does not process
// target's neighbors)
void dijkstra(ll n, const vvpl& graph, vl& dist, ll start, ll target = -1LL)
{
    rep(i, 0, len(dist))
    {
        dist[i] = LONG_LONG_MAX;
    }
    set<pl> pq;

    pq.insert({ 0, start });
    dist[start] = 0;
    while (!pq.empty()) {
        auto [distance, node] = *(pq.begin());
        pq.erase({ distance, node });

        if (node == target) {
            break;
        }

        foreachp(child, edge, graph[node])
        {
            if (distance + edge < dist[child]) {
                pq.erase({ dist[child], child });
                pq.insert({ distance + edge, child });
                dist[child] = distance + edge;
            }
        }
    }
}
