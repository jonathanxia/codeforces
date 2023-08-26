#include <lib/vv.h>

#include <lib/sparsetable.h>

struct DfsForest {
    vvpl graph;
    ll n;

    vl height; // From the root
    vl weighted_height; // From the root
    vl num_desc; // Including myself
    vl deepest_leaf; // Leaf is 0

    vl counter_to_node;
    vl node_to_counter;

    vl subtree_order; // With counters
    vl dfs_order; // With counters

    vl parent;

    ll cnter = 0;

    DfsForest(const vvpl& g, ll root) : graph(g) {
        n = len(graph);

        height.resize(n, 0);
        weighted_height.resize(n, 0);
        num_desc.resize(n, 0);
        deepest_leaf.resize(n, 0);
        parent.resize(n, -1);

        inv_dfs_order_left.resize(n, -1);
        inv_dfs_order_right.resize(n, -1);
        inv_subtree_order.resize(n, -1);
        counter_to_node.resize(n, -1);
        node_to_counter.resize(n, -1);

        cnter = 0;

        dfs(root, -1);
    }

    void dfs(ll node, ll par) {
        parent[node] = par;
        // Visiting a new node, get a counter
        ll my_counter = cnter++;
        counter_to_node[my_counter] = node;
        node_to_counter[node] = my_counter;

        dfs_order.pb(my_counter);
        subtree_order.pb(my_counter);

        num_desc[node]++;
        deepest_leaf[node] = 0;
        foreachp(child, w, graph[node]) {
            if (child == par) continue;

            weighted_height[child] = weighted_height[node] + w;
            height[child] = height[node] + 1;

            dfs(child, node);
            num_desc[node] += num_desc[child];
            chkmax(deepest_leaf[node], 1 + deepest_leaf[child]);

            dfs_order.pb(my_counter);
        }
    }
};

struct LCATree {
    DFSForest forest;
    SparseTable st;

    vl node_to_pos_in_dfs_order;
    LCATree(const DFSForest& f) : forest(f) {
        st = SparseTable(forest.dfs_order, [](ll x, ll y) { return min(x, y); });
        ll n = forest.graph.size();
        node_to_pos_in_dfs_order = vl(n);
        rep(j, 0, len(forest.dfs_order) - 1) {
            node_to_pos_in_dfs_order[forest.dfs_order[j]] = j;
        }
    }

    ll lca(ll a, ll b) {
        ll idxa = node_to_pos_in_dfs_order[a];
        ll idxb = node_to_pos_in_dfs_order[b];

        ll mn = st.query(idxa, idxb);
        return forest.counter_to_node[mn];
    }
};