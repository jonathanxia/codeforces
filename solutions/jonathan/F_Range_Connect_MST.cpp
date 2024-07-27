// Link: https://atcoder.jp/contests/abc364/tasks/abc364_f
#include <lib/vv/sort.h>
#include <lib/commit_dsu.h>
using namespace vv;

void solve() {
    ll n, q; cin >> n >> q;
    vector<array3> queries(q);
    FOR(i, 0, q - 1) {
        cin >> queries[i][1] >> queries[i][2] >> queries[i][0];
    }
    sort(queries);
    DSU dsu(n);
    vb marked(n);
    ll ans = 0;
    foreach(query, queries) {
        auto [c, L, R] = query;
        L--; R--;

        ll idx = L;
        set<ll> comps;
        while (idx <= R) {
            ll comp = dsu.find(idx);
            comps.insert(comp);
            ll r_x = dsu.largest[comp];
            idx = r_x + 1;
        }
        // Have more than one component
        ans += len(comps) * c;
        ll comp = *comps.begin();
        foreach(o_comp, comps) {
            dsu.unite(o_comp, comp);
        }
    }
    FOR(i, 0, n - 1) {
        if (dsu.find(i) != dsu.find(0)) {
            print(-1); return;
        }
    }
    print(ans);

}

int main() {
    init();
    solve();
    return 0;
}