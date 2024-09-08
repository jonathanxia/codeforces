// Link: https://codeforces.com/contest/1679/problem/D

#include <lib/common.h>
#include <lib/graph/topo_sort.h>
#include <lib/inp.h>
#include <lib/macros.h>
#include <lib/print.h>
#include <lib/vv/max.h>

void solve()
{
    ll n, m, k;
    cin >> n >> m >> k;
    vl a(n);
    cin >> a;
    vvl adj(n);
    cepeat(m)
    {
        ll u, v;
        cin >> u >> v;
        u--;
        v--;
        adj[u].pb(v);
    }

    auto works = [&](ll max_allowed) {
        usetl excluded;
        walk(i, a)
        {
            if (a[i] > max_allowed) {
                excluded.insert(i);
            }
        }
        bool has_cycle;
        vl topo = graph::topo_sort(adj, has_cycle, excluded);
        if (has_cycle)
            return true;
        vl maxi(n, -1);
        reverse_walk(i, topo)
        {
            ll node = topo[i];
            ll best_length = 0;
            foreach (neighbor, adj[node]) {
                if (excluded.count(neighbor))
                    continue;
                chkmax(best_length, maxi[neighbor]);
            }
            best_length++;
            maxi[node] = best_length;
        }
        return vv::max(maxi) >= k;
    };
    ll x = smallest_st(i, works(i), 0, 1e9);
    if (x > 1e9) {
        print(-1);
    } else {
        print(x);
    }
}

int main()
{
    init();
    solve();
    return 0;
} //