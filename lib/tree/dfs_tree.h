#pragma once
#include <lib/common.h>

struct DfsTree {
    int n;
    int root;

    vi height; // From the root
    vl weighted_height; // From the root
    vi num_desc; // Including myself
    vi deepest_leaf; // Leaf is 0
    vl deepest_weighted_leaf; // Leaf is 0

    vi counter_to_node;
    vi node_to_counter;

    vi subtree_order; // With node values
    vi dfs_order; // With counters

    // These are "time in" and "time out" when traversing
    // DFS through the tree.
    vi tin; // node->time
    vi tout; // node->time

    vi parent;

    vb visited;

    int cnter = 0;

    DfsTree(const vvpl& g, ll root_) : root(root_)
    {
        n = len(g);

        height.resize(n, 0);
        weighted_height.resize(n, 0);
        num_desc.resize(n, 0);
        deepest_leaf.resize(n, 0);
        deepest_weighted_leaf.resize(n, 0);
        parent.resize(n, -1);

        counter_to_node.resize(n, -1);
        node_to_counter.resize(n, -1);

        tin.resize(n, 1e9);
        tout.resize(n, -1);

        visited.resize(n, false);

        cnter = 0;

        dfs(root, -1, g);

        walk(t, dfs_order) {
            ll node = counter_to_node[dfs_order[t]];
            chkmin(tin[node], t);
            chkmax(tout[node], t);
        }
    }

    void dfs(ll node, ll par, const vvpl& g)
    {
        visited[node] = true;

        parent[node] = par;
        // Visiting a new node, get a counter
        ll my_counter = cnter++;
        counter_to_node[my_counter] = node;
        node_to_counter[node] = my_counter;

        dfs_order.pb(my_counter);
        subtree_order.pb(node);

        num_desc[node]++;
        deepest_leaf[node] = 0;
        deepest_weighted_leaf[node] = 0;
        foreachp(child, w, g[node])
        {
            if (visited[child]) continue;

            weighted_height[child] = weighted_height[node] + w;
            height[child] = height[node] + 1;

            dfs(child, node, g);
            num_desc[node] += num_desc[child];
            chkmax(deepest_leaf[node], 1 + deepest_leaf[child]);
            chkmax(deepest_weighted_leaf[node], w + deepest_weighted_leaf[child]);

            dfs_order.pb(my_counter);
        }
    }

    // Returns if u is an ancestor of v
    bool is_ancestor(ll u, ll v) {
        ll cu = node_to_counter[u];
        ll cv = node_to_counter[v];

        return ordered(cu, cv, cu + num_desc[u] - 1);
    }
};

