// Link: https://codeforces.com/contest/2020/problem/D

#include<lib/macros.h>
#include<lib/print.h>
#include<lib/inp.h>
#include<lib/common.h>
#include<lib/dsu.h>
#include<lib/vv/max.h>
#include<lib/cum.h>
#include<lib/vv/sort.h>
#include<lib/intervals.h>

void solve()
{
    ll n, m;
    cin >> n >> m;

    vector<vvpl> intervals(11);
    rep(i, 1, 11)
    {
        intervals[i] = vvpl(i);
    }
    // process updates
    cepeat(m)
    {
        ll a, d, k;
        cin >> a >> d >> k;
        a--;
        pl interval { a, a + d * k };
        intervals[d][a % d].pb(interval);
    }
    // unify intervals
    rep(i, 1, 11)
    {
        rep(j, 0, i)
        {
            intervals::unify(intervals[i][j]);
        }
    }
    // each node is actually 10 nodes
    DSU dsu(n * 10);
    rep(i, 0, n)
    {
        rep(j, 0, 10)
        {
            dsu.unite(i, j * n + i);
        }
    }
    // now apply the updates
    rep(i, 1, 11)
    {
        rep(j, 0, i)
        {
            foreach (interval, intervals[i][j]) {
                ll offset = (i - 1) * n;
                SFOR(k, interval.first, interval.second, i)
                {
                    dsu.unite(offset + interval.first, offset + k);
                }
            }
        }
    }
    set<ll> comps;
    rep(i, 0, n)
    {
        comps.insert(dsu.find(i));
    }
    print(comps.size());
}

int main()
{
    init();
    int t;
    cin >> t;
    cep(t) solve();
    return 0;
}