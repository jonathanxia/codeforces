// Link: https://codeforces.com/contest/1996/problem/G
#include <lib/commit_dsu.h>
#include <lib/datastruct/acsegtree/lazy_sum_min_count.h>
#include <lib/mset.h>

void solve() {
    ll n, m; cin >> n >> m;
    DSU dsu(n);
    cepeat(m) {
        ll a, b; cin >> a >> b;
        a--; b--;
        dsu.unite(a, b);
    }
    map<ll, set<ll>> components;
    FOR(v, 0, n - 1) {
        components[dsu.find(v)].insert(v);
    }

    auto seg = lazy_sum_min_count::init(vl(2 * n, 0));
    ll ans = 1e18;

    foreachp(c, _, components) {
        ll mn = mset::min(components[c]);
        ll mx = mset::max(components[c]);
        if (mx > mn)
            seg.update(mn, mx - 1, 1);
    }
    auto run_query = [&](ll i) {
        pl res = seg.query(i, i + n - 2);
        if (res.first > 0) {
            chkmin(ans, n - 1);
        }
        else {
            chkmin(ans, n - res.second - 1);
        }
    };
    run_query(0);

    FOR(i, 1, n - 1) {
        // i - 1 now turns into i - 1 + n
        ll cc = dsu.find(i - 1);
        ll mn = mset::min(components[cc]);
        ll mx = mset::max(components[cc]);
        if (mx > mn)
            seg.update(mn, mx - 1, -1);
        components[cc].erase(i - 1);
        components[cc].insert(i - 1 + n);
        mn = mset::min(components[cc]);
        mx = mset::max(components[cc]);
        if (mx > mn)
            seg.update(mn, mx - 1, 1);
        run_query(i);
    }
    print(ans);
}

int main() {
    init();
    int t; cin >> t;
    cep(t) solve();
    return 0;
}