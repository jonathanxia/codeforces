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
    vvi ancestors; // ancestors[i][v] gives the 2^i-th ancestor of v
    const ll log_depth = 30; // length of ancestors

    AncestorTree(const DfsTree& tree) {
        ll n = tree.graph.size();
        ancestors = vvi(log_depth, vi(n));
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
        ll ret = v;
        FOR(i, 0, log_depth - 1) {
            if ((1LL << i) > k) break;
            if ((1LL << i) & k) {
                ret = ancestors[i][ret];
            }
        }
        return ret;
    }
};

// Data structure for efficient range queries on the tree.
template <typename T>
struct BinaryLiftingTree {
    AncestorTree ast;
    vector<vector<T>> cumulative;

    function<T(T, T)> merge_func;

    BinaryLiftingTree(const DfsTree& tree, const vector<T>& values, function<T(T, T)> merge_func_)
        : ast(tree)
        , merge_func(merge_func_)
    {
        ll log_depth = ast.log_depth;
        ll n = tree.graph.size();

        cumulative = vector<vector<T>>(log_depth, vector<T>(n));

        FOR(i, 0, n - 1) {
            cumulative[0][i] = values[i];
        }

        FOR(i, 1, log_depth - 1) {
            FOR(vert, 0, n - 1) {
                ll kp = ast.ancestors[i - 1][vert];
                cumulative[i][vert] = merge_func(cumulative[i - 1][vert], cumulative[i - 1][kp]);
            }
        }
    }

    // query(k, v) returns the merge func applied
    // on the nodes from v to the k-th ancestor of v,
    // inclusive. So k=0 means get the value itself

    // This version takes log time because it doesn't assume
    // idempotency
    T query(ll k, ll v) {
        T ans = cumulative[0][v];
        v = ast.ancestors[0][v];

        FOR(i, 0, ast.log_depth - 1) {
            if ((1LL << i) > k) break;
            if ((1LL << i) & k) {
                ans = merge_func(ans, cumulative[i][v]);
                v = ast.ancestors[i][v];
            }
        }

        return ans;
    }

    // Performs o(1) time query by assuming idempotency
    T query1(ll k, ll v) {
        T ans = cumulative[0][v];
        v = ast.ancestors[0][v];
        if (k == 0) return ans;

        // We must be very careful here, because the
        // cumulative queries are off by one

        // We want v + 1 -> v + k, inclusive
        // which means we want v + 1 -> v + 2^j union v + k - (2^j - 1) -> v + k
        // this requires 2^j >= k - 2^j + 1 --> 2^(j + 1) >= k + 1
        // but also 2^j <= k

        ll J = 1; // = 2^j
        ll j = 0;
        while (2 * J < k + 1) {
            J *= 2; j++;
        }

        ll v1 = ast.get_ancestor(k - J, v);
        return merge_func(ans, merge_func(cumulative[j][v], cumulative[j][v1]));
    }
};