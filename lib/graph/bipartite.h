#pragma once

#include <lib/common.h>

namespace graph {
    // Returns whether the graph is bipartite.
    // If it is, the color parameter will store what the coloring
    // is. The output of color is either 0 or 1.
    bool isBipartite(const vvpl& graph, vector<int>& color) {
        int n = graph.size();
        color.assign(n, -1); // -1 indicates uncolored

        for (int start = 0; start < n; ++start) {
            if (color[start] == -1) { // If the node is not colored
                queue<int> q;
                q.push(start);
                color[start] = 0; // Start coloring with 0

                while (!q.empty()) {
                    int u = q.front();
                    q.pop();

                    for (const auto& [v, w] : graph[u]) {
                        if (color[v] == -1) { // If the neighbor is not colored
                            color[v] = 1 - color[u]; // Assign an alternate color
                            q.push(v);
                        } else if (color[v] == color[u]) { // If the neighbor has the same color
                            return false; // The graph is not bipartite
                        }
                    }
                }
            }
        }
        return true; // The graph is bipartite
    }

    bool _bfsFindOddCycle(const vvpl& graph, int start, vector<int>& color, vector<int>& parent, vector<ll>& cycle) {
        int n = graph.size();
        queue<int> q;
        q.push(start);
        color[start] = 0;

        while (!q.empty()) {
            int u = q.front();
            q.pop();

            for (const auto& [v, w] : graph[u]) {
                if (color[v] == -1) {
                    color[v] = 1 - color[u];
                    parent[v] = u;
                    q.push(v);
                } else if (color[v] == color[u]) {
                    // Found an odd-length cycle
                    int x = u, y = v;
                    while (x != y) {
                        cycle.push_back(x);
                        cycle.push_back(y);
                        x = parent[x];
                        y = parent[y];
                    }
                    cycle.push_back(x); // Add the common ancestor
                    return true;
                }
            }
        }
        return false;
    }

    // Finds an odd cycle and returns it. If the graph is
    // bipartite, then returns an empty list.
    vector<ll> findOddCycle(const vvpl& graph) {
        int n = graph.size();
        vector<int> color(n, -1);
        vector<int> parent(n, -1);
        vector<ll> cycle;

        for (int start = 0; start < n; ++start) {
            if (color[start] == -1) {
                if (_bfsFindOddCycle(graph, start, color, parent, cycle)) {
                    return cycle;
                }
            }
        }
        return vl();
    }

} // namespace graph
