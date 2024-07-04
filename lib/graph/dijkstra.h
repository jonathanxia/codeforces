#pragma once
#include <lib/common.h>

namespace graph {
    // Specify target to stop Dijkstra once target is processed (does not process
    // target's neighbors)
    void dijkstra(const vvpl &graph, vl &dist, const vl& starts, ll target = -1LL)
    {
        rep(i, 0, len(dist))
        {
            dist[i] = LLONG_MAX;
        }
        set<pl> pq;

        foreach(start, starts) {
            pq.insert({0, start});
            dist[start] = 0;
        }
        while (!pq.empty())
        {
            auto [distance, node] = *(pq.begin());
            pq.erase({distance, node});

            if (node == target)
            {
                break;
            }

            foreachp(child, edge, graph[node])
            {
                if (distance + edge < dist[child])
                {
                    pq.erase({dist[child], child});
                    pq.insert({distance + edge, child});
                    dist[child] = distance + edge;
                }
            }
        }
    }

    void dijkstra(const vvpl& graph, vl& dist, ll start, ll target=-1LL) {
        dijkstra(graph, dist, vl({start}), target);
    }
} // namespace graph