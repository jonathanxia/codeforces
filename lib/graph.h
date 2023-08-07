#include "common.h"

namespace graph {
// Specify target to stop Dijkstra once target is processed (does not process
// target's neighbors)
void dijkstra(const vvpl& graph, vl& dist, ll start, ll target = -1LL)
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
// Returns weight of minimum/maximum spanning tree, and stores the tree in edges
// Use seed to specify a starting point from which to run Prim's.

ll prim(const vvpl& graph, vpl& edges, bool minimum = true, ll seed = 0LL)
{
    set<tuple<ll, ll, ll>> heap;
    auto heap_top = [&]() {
        if (minimum)
            return *(heap.begin());
        else
            return *(heap.rbegin());
    };
    auto heap_pop = [&]() {
        if (minimum)
            heap.erase(*(heap.begin()));
        else
            heap.erase(*(heap.rbegin()));
    };
    ll n = len(graph);
    vb in_tree(n, false);
    ll total_weight = 0;

    // initialize the tree
    in_tree[seed] = true;
    foreachp(neighbor, weight, graph[seed])
    {
        heap.insert({ weight, seed, neighbor });
    }

    while (!heap.empty()) {
        // ignore top of the heap if the endpoint is already included
        if (in_tree[get<2>(heap_top())]) {
            heap_pop();
            continue;
        }
        auto edge = heap_top();
        // add endpoint to tree
        in_tree[get<2>(edge)] = true;
        total_weight += get<0>(edge);
        edges.pb({ get<1>(edge), get<0>(edge) });

        // look through neighbors of endpoint and add them to the heap
        foreachp(neighbor, weight, graph[get<2>(edge)])
        {
            if (!in_tree[neighbor])
                heap.insert({ weight, get<2>(edge), neighbor });
        }
    }
    return total_weight;
}
}
