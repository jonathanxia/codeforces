#pragma once
#include <lib/common.h>

namespace graph {
    /**
     * Algorithm for finding bridges. Takes in a graph in vvpl format and
     * returns a list of bridges.
     * 
     * Usage: https://codeforces.com/contest/1986/submission/267101976
     * 
     * 
     */
    vector<pl> find_bridges(const vvpl& graph) {
        ll n = len(graph);
        vb visited(n);
        vpl output;

        // Smallest descendant of v
        vl smallest_desc(n, 1e18);
        vl visit_time(n, 0);
        ll t = 0;
        function<void(ll, ll)> dfs = [&](ll node, ll parent) {
            visited[node] = true;
            visit_time[node] = t++;
            chkmin(smallest_desc[node], visit_time[node]);

            foreachp(child, w, graph[node]) {
                if (!visited[child]) {
                    // In this case, we know that node->child is a dfs tree
                    // edge, so it is a candidate to be a bridge.
                    dfs(child, node);
                    if (smallest_desc[child] == visit_time[child]) {
                        output.push_back({node, child});
                    }
                }

                if (child != parent) {
                    chkmin(smallest_desc[node], smallest_desc[child]);
                }
            }
        };
        FOR(i, 0, n - 1) {
            if (!visited[i]) dfs(i, -1);
        }

        return output;
    }
} // namespace graph