// Link: https://codeforces.com/contest/1923/problem/E

#include<lib/tree/aux_tree.h>
#include<lib/common.h>


void solve() {
    ll n; cin >> n;
    vi color(n);
    vvi colors(n + 1);
    FOR(i, 0, n - 1) {
        ll c; cin >> c;
        colors[c].pb(i);
        color[i] = c;
    }
    vvpl graph(n);
    inp::read_tree(graph);

    DfsTree tree(graph, 0);
    LCATree lca_tree(tree);
    ll ans = 0;
    vl num_child(n, 0);
    FOR(c, 1, n) {
        if (len(colors[c]) == 0) continue;
        AuxTree aux_tree(lca_tree, colors[c]);
        function<void(ll)> dfs = [&](ll node) {
            num_child[node] = 0;
            ll nc = 0;
            ll nc2 = 0;
            foreach(child, aux_tree.vg[node]) {
                dfs(child);
                nc += num_child[child];
                nc2 += num_child[child] * num_child[child];
            }
            if (color[node] == c) {
                ans += nc;
                num_child[node] = 1;
            }
            else {
                ans += (nc * nc - nc2) / 2;
                num_child[node] = nc;
            }
        };
        dfs(aux_tree.root);
    }
    print(ans);
}

int main() {
    init();
    int t; cin >> t;
    cep(t) solve();
    return 0;
}