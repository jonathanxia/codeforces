#include "../../common.h"
// Encoding for nodes; typically use ll, but may be more complicated like pl
using node_t = ll;
// Used for returning distances; if using non-trivial node_t, use
// a umap with ll as key (eg. umap<pl, ll>)
using dijkstra_t = umap<node_t, ll>;
// using dijkstra_t = vl;
using neighbor_t = vector<pair<node_t, ll>>;

function<const neighbor_t(const node_t&)> neighbor_gen = [&](const node_t& node) -> const neighbor_t {
    // Used for generating {neighbors, edge weight} pairs of node
    // For example, with adjacency list adj:
    // return adj[node];
};

function<dijkstra_t(node_t, node_t, bool)> dijkstra = [&](node_t start, node_t target, bool stop_at_target) -> dijkstra_t {
    dijkstra_t distances;
    distances[start] = 0LL;
    set<pair<ll, node_t>> heap;
    heap.insert({ 0LL, start });
    while (!heap.empty()) {
        auto [distance, node] = *heap.begin();
        heap.erase({ distance, node });
        if (stop_at_target && node == target) {
            break;
        }
        neighbor_t neighbors = neighbor_gen(node);
        foreachp(neighbor, edge, neighbors)
        {
            if (!distances.count(neighbor) || distance + edge < distances[neighbor]) {
                heap.erase({ distances[neighbor], neighbor });
                heap.insert({ distance + edge, neighbor });
                distances[neighbor] = distance + edge;
            }
        }
    }
    return distances;
};