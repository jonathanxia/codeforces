// Link: https://codeforces.com/contest/1975/problem/E
#include <lib/common.h>
#include <lib/tree/lca_tree.h>
#include <lib/tree/path_sum_tree.h>
#include <lib/mset.h>
#include <lib/vv/sum.h>

void solve() {
    ll n, q; cin >> n >> q;
    vl c(n); cin >> c;
    vvpl graph(n);
    inp::read_tree(graph);
    DfsTree tree(graph, 0);
    LCATree lca_tree(tree);
 
    // Data structures to maintain
    ll num_black = vv::sum(c);
    set<ll> black_leaves;
    vl num_black_children(n);
    PathSumTree ps_tree(lca_tree, c);
 
    // Initialize all data structures
    function<void(ll, ll)> dfs = [&](ll node, ll parent) {
        foreachp(child, w, graph[node]) if (child != parent) {
            dfs(child, node);
            if (c[child]) num_black_children[node]++;
        }
        // Am I a black leaf?
        if (c[node] && num_black_children[node] == 0)
            black_leaves.insert(node);
    };
    dfs(0, -1);
 
    cepeat(q) {
        ll u; cin >> u; u--;
 
        // Update the data structures
        if (c[u] == 0) {
            // Need to change from white to black
            c[u] = 1;
            num_black++;
            if (u != 0) {
                num_black_children[tree.parent[u]]++;
                black_leaves.erase(tree.parent[u]);
            }
            if (num_black_children[u] == 0) black_leaves.insert(u);
            ps_tree.update(u, 1);
        }
        else {
            c[u] = 0;
            num_black--;
            if (u != 0) {
                ll p = tree.parent[u];
                num_black_children[p]--;
                if (num_black_children[p] == 0 && c[p] == 1) {
                    black_leaves.insert(p);
                }
            }
            black_leaves.erase(u);
            ps_tree.update(u, -1);
        }
 
        // Answer the query
        dbg(num_black);
        dbg(black_leaves);
        dbg(num_black_children);
        if (num_black == 0) { print("No"); continue; }
        if (len(black_leaves) > 2) { print("No"); continue; }
        // Now we either have one black leaf or two black leaves
        if (len(black_leaves) == 1) { print("Yes"); continue; }
        // Two black leaves
        ll leaf1 = mset::min(black_leaves);
        ll leaf2 = mset::max(black_leaves);
 
        ll num_b_on_path = ps_tree.query(leaf1, leaf2);
        if (num_b_on_path == num_black && num_b_on_path == lca_tree.dist(leaf1, leaf2) + 1) {
            print("Yes"); continue;
        }
        else {
            print("No");
        }
    }
}
 
int main() {
    init();
    int t; cin >> t;
    cep(t) solve();
    return 0;
}