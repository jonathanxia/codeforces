// Link: https://codeforces.com/contest/1980/problem/G
#include<lib/string/bit_trie.h>
#include<lib/dfs.h>
#include<lib/common.h>

void solve() {
    ll n, m; cin >> n >> m;
    vvpl graph(n);
    cepeat(n - 1) {
        ll u, v, w; cin >> u >> v >> w; u--; v--;
        graph[u].pb({v, w});
        graph[v].pb({u, w});
    }
    DfsTree tree(graph, 0);

    vl value(n);
    array<str::BitTrie<ll, 31>, 2> tries; {
        // Collect the values
        function<void(ll, ll, ll)> dfs = [&](ll node, ll parent, ll depth) {
            foreachp(child, w, graph[node]) {
                if (child == parent) continue;
                value[child] = w ^ value[node];
                dfs(child, node, depth + 1);
            }
            tries[depth % 2].add(value[node], 1);
        };
        dfs(0, -1, 0);
    }

    ll toggle = 0;
    vl output;
    cepeat(m) {
        char typ; cin >> typ;
        if (typ == '^') {
            ll y; cin >> y; toggle ^= y;
            continue;
        }
        ll v, x; cin >> v >> x; v--;

        // Calculate the value of v
        ll val = value[v];
        // Remove the value of v
        tries[tree.height[v] % 2].add(val, -1);

        // Now we try to find the maximum XOR
        ll val_actual = val;
        if (tree.height[v] % 2 == 1) val_actual ^= toggle;
        ll ans = 0;
        chkmax(ans, tries[0].max_xor(val_actual ^ x));
        chkmax(ans, tries[1].max_xor(val_actual ^ x ^ toggle));

        // Add the value of v back
        tries[tree.height[v] % 2].add(val, 1);

        output.pb(ans);
    }
    print(output);
}

int main() {
    init();
    int t; cin >> t;
    cep(t) solve();
    return 0;
}