// Link: https://codeforces.com/contest/1988/problem/D

#include<lib/macros.h>
#include<lib/print.h>
#include<lib/inp.h>
#include<lib/common.h>
#include<lib/cum.h>
#include<lib/tree/dfs_tree.h>
#include<lib/dfs.h>
#include<lib/ndarray.h>

void solve()
{
    ll n;
    cin >> n;
    vl a(n);
    cin >> a;
    vvpl adj(n);
    cepeat(n - 1)
    {
        ll x, y;
        cin >> x >> y;
        x--;
        y--;
        adj[x].pb({ y, 1 });
        adj[y].pb({ x, 1 });
    }
    DfsTree dfs(adj, 0);
    vvl children(n);
    rep(i, 0, n)
    {
        if (dfs.parent[i] != -1)
            children[dfs.parent[i]].pb(i);
    }

    ll LOG = 20;
    vector<cum::min<ll>> cums(n);

    DOR(counter, n - 1, 0)
    {
        ll node = dfs.counter_to_node[counter];
        vl base;
        rep(i, 0, LOG)
        {
            ll cost = (i + 1) * a[node];
            foreach (child, children[node]) {
                cost += cums[child].all_except(i, i);
            }
            base.pb(cost);
        }
        cums[node] = cum::min<ll>(base);
    }
    print(cums[0].query(0, n - 1));
}

int main()
{
    init();
    int t;
    cin >> t;
    cep(t) solve();
    return 0;
}