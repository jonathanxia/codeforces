#pragma once
#include <lib/sparsetable.h>
#include <lib/tree/dfs_tree.h>

struct LCATree {
    const DfsTree& forest;
    SparseTable<int> st;

    vi counter_to_pos_in_dfs_order;
    LCATree(const DfsTree& f)
        : forest(f), st(forest.dfs_order, [](int x, int y) { return min(x, y); })
    {
        ll n = forest.n;
        counter_to_pos_in_dfs_order = vi(n);
        FOR(j, 0, len(forest.dfs_order) - 1)
        {
            counter_to_pos_in_dfs_order[forest.dfs_order[j]] = j;
        }
    }

    /**
     * Returns the lca of nodes a and b in the tree
    */
    ll lca(ll a, ll b) const
    {
        a = forest.node_to_counter[a];
        b = forest.node_to_counter[b];
        ll idxa = counter_to_pos_in_dfs_order[a];
        ll idxb = counter_to_pos_in_dfs_order[b];

        ll mn = st.query(min(idxa, idxb), max(idxa, idxb));
        return forest.counter_to_node[mn];
    }

    /**
     * Returns the distance between nodes a and b in the tree.
    */
    ll dist(ll a, ll b) const {
        ll l = lca(a, b);
        return forest.height[a] + forest.height[b] - 2 * forest.height[l];
    }

    /**
     * Returns the weighted distance between nodes a and b in the tree.
    */
    ll weighted_dist(ll a, ll b) const {
        ll l = lca(a, b);
        return forest.weighted_height[a] + forest.weighted_height[b] - 2 * forest.weighted_height[l];
    }
};
