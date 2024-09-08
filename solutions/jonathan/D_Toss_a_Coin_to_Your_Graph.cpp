// Link: https://codeforces.com/contest/1679/problem/D
#include <lib/constants/mod998244353.h>
#include <lib/vv/sum.h>
#include <lib/vv/counter.h>
#include <lib/vv/sort.h>
#include <atcoder/scc>
#include <lib/vv/max.h>
#include <lib/mem.h>
using namespace vv;

void solve() {
    ll n, m, k; cin >> n >> m >> k;
    vl a(n); cin >> a;
    vvpl graph(n);
    cepeat(m){ 
        ll u, v; cin >> u >> v; u--; v--;
        graph[u].pb({v, 1});
    }
    auto func = [&](ll cutoff) {
        atcoder::scc_graph g(n);
        FOR(u, 0, n - 1) {
            if (a[u] > cutoff) continue;
            foreachp(v, w, graph[u]) if (a[v] <= cutoff) {
                g.add_edge(u, v);
            }
        }
        vvi components = g.scc();
        if (exists_st(i, components[i].size() > 1, 0, len(components) - 1)) {
            return true;
        }
        // No cycles exists, so we do the dp
        vl dp(n, -1);
        DOR(i, len(components) - 1, 0) {
            ll u = components[i][0];
            if (a[u] <= cutoff) dp[u] = 0;
            if (a[u] <= cutoff) foreachp(v, w, graph[u]) if (a[v] <= cutoff) {
                chkmax(dp[u], 1 + dp[v]);
            }
        }
        return vv::max(dp) >= k - 1;
    };
    ll ans = smallest_st(cutoff, func(cutoff), 0, ll(1e11));
    if (ans >= 1e10) {
        print(-1);
    }
    else {
        print(ans);
    }
}

int main() {
    init();
    solve();
    return 0;
}