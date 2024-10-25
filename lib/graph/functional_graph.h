#pragma once
#include <lib/common.h>

namespace graph {
    // Finds cycles for directed graphs where degree of every node is 1
    // is1idx refers to whether the elements in the array adj start at 0 or at 1.
    // is1idx = true is equivalent to subtracting 1 from everything in adj, then adding 1 to everything in cycles.
    // behavior of in_cycle and in_chain does not change when is1idx is set to true.
    // Returns a vvl: vector of the cycles in the graph
    vvl cycles(const vl& adj, vb& in_cycle, vb& in_chain, bool is1idx = false)
    {
        vvl cycles_;
        walk(i, adj)
        {
            ll slow = i;
            ll fast = i;
            do {
                if (in_chain[slow] || in_cycle[slow] || in_chain[fast] || in_cycle[fast])
                    break;
                slow = adj[slow] - is1idx;
                fast = adj[adj[fast] - is1idx] - is1idx;
            } while (slow != fast);
            if (slow == fast && !in_cycle[slow] && !in_chain[slow]) {
                vl cycle;
                // now slow and fast are equal, they must be in a cycle
                while (!in_cycle[slow]) {
                    in_cycle[slow] = true;
                    cycle.pb(slow);
                    slow = adj[slow] - is1idx;
                }
                cycles_.pb(cycle);
            }
            fast = i;
            while (!in_cycle[fast] && !in_chain[fast]) {
                in_chain[fast] = true;
                fast = adj[fast] - is1idx;
            }
        }
        return cycles_;
    }

    // Finds cycles for directed graphs where degree of every node is 1
    struct FunctionalGraph {
        vb in_cycle;
        vb in_chain;
        const vl& adj;
        vvl cycs;

        vvl children; // Each node in the cycle has a tree, this defines it

        vl cycle_number;
        vl dist_from_cycle;

        FunctionalGraph(const vl& adj_, bool is1idx = false) :
            in_cycle(len(adj_)),
            in_chain(len(adj_)),
            adj(adj_),
            children(len(adj_)),
            cycle_number(len(adj_), -1),
            dist_from_cycle(len(adj_))
        {
            cycs = cycles(adj, in_cycle, in_chain, is1idx);

            walk(i, cycs) {
                foreach(v, cycs[i]) cycle_number[v] = i;
            }

            ll n = len(adj);
            FOR(i, (int) is1idx, n - 1) {
                dfs(i);
            }

            FOR(i, (int) is1idx, n - 1) {
                if (in_chain[i]) children[adj[i]].pb(i);
            }
        }

        void dfs(ll node) {
            ll child = adj[node];
            if (cycle_number[node] != -1) {
                return;
            }
            dfs(child);
            cycle_number[node] = cycle_number[child];
            dist_from_cycle[node] = 1 + dist_from_cycle[child];
        }
    };
} // namespace graph
