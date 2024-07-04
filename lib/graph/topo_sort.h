#pragma once
#include <lib/common.h>

namespace graph {
    // Returns a topological sort order of a dag
    // If dag is not actually a dag, this will return a vl that is shorter than dag
    vl topo_sort(const vvl &dag)
    {
        ll n = len(dag);
        vl order;
        vb DFS_processed(n, false);
        vb DFS_processing(n, false);
        bool found_cycle = false;
        function<void(ll)> DFS = [&](ll node) -> void
        {
            if (found_cycle)
                return;
            if (DFS_processed[node])
                return;
            DFS_processing[node] = true;
            foreach (child, dag[node])
            {
                if (DFS_processing[child])
                {
                    // found cycle!
                    dprint("Potential error: topo_sort found a cycle in graph");
                    found_cycle = true;
                    return;
                }
                if (!DFS_processed[child])
                {
                    DFS(child);
                }
            }
            DFS_processed[node] = true;
            DFS_processing[node] = false;
            order.pb(node);
        };
        rep(i, 0, n)
        {
            DFS(i);
        }
        reverse(order.begin(), order.end());
        return order;
    }
} // namespace graph 