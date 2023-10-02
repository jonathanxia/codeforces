#include <lib/vv.h>

#include <lib/sparsetable.h>

struct DfsTree {
    vvpl graph;
    ll n;
    ll root;

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

    DfsTree(const vvpl& g, ll root_)
        : graph(g), root(root_)
    {
        n = len(graph);

        height.resize(n, 0);
        weighted_height.resize(n, 0);
        num_desc.resize(n, 0);
        deepest_leaf.resize(n, 0);
        parent.resize(n, -1);

        counter_to_node.resize(n, -1);
        node_to_counter.resize(n, -1);

        cnter = 0;

        dfs(root, -1);
    }

    void dfs(ll node, ll par)
    {
        parent[node] = par;
        // Visiting a new node, get a counter
        ll my_counter = cnter++;
        counter_to_node[my_counter] = node;
        node_to_counter[node] = my_counter;

        dfs_order.pb(my_counter);
        subtree_order.pb(my_counter);

        num_desc[node]++;
        deepest_leaf[node] = 0;
        foreachp(child, w, graph[node])
        {
            if (child == par)
                continue;

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
    DfsTree forest;
    SparseTable st;

    vl counter_to_pos_in_dfs_order;
    LCATree(const DfsTree& f)
        : forest(f), st(forest.dfs_order, [](ll x, ll y) { return min(x, y); })
    {
        ll n = forest.graph.size();
        counter_to_pos_in_dfs_order = vl(n);
        FOR(j, 0, len(forest.dfs_order) - 1)
        {
            counter_to_pos_in_dfs_order[forest.dfs_order[j]] = j;
        }
    }

    ll lca(ll a, ll b)
    {
        a = forest.node_to_counter[a];
        b = forest.node_to_counter[b];
        ll idxa = counter_to_pos_in_dfs_order[a];
        ll idxb = counter_to_pos_in_dfs_order[b];

        ll mn = st.query(min(idxa, idxb), max(idxa, idxb));
        return forest.counter_to_node[mn];
    }
};

struct AncestorTree {
    vvl ancestors; // ancestors[i][v] gives the 2^i-th ancestor of v
    ll log_depth = 30; // length of ancestors
    AncestorTree(const DfsTree& tree) {
        ll n = tree.graph.size();
        ancestors = vvl(log_depth, vl(n));
        FOR(i, 0, n - 1) {
            // Induces a self-loop for the parent
            ancestors[0][i] = (i == tree.root) ? i : tree.parent[i];
        }

        FOR(i, 1, log_depth - 1) {
            FOR(vert, 0, n - 1) {
                ll kp = ancestors[i - 1][vert];
                ancestors[i][vert] = ancestors[i - 1][kp];
            }
        }
    }

    // Get the k-th ancestor of vertex v
    ll get_ancestor(ll k, ll v) {
        if(k == 0) return v;
        ll ret = v;
        FOR(i, 1, log_depth - 1) {
            if ((1LL << i) & k) {
                ret = ancestors[i][ret];
            }
        }
        return ret;
    }
};