// Link: https://atcoder.jp/contests/abc371/tasks/abc371_g
#include<lib/constants/mod998244353.h>
#include<lib/common.h>
#include<lib/vv/sum.h>
#include<lib/vv/counter.h>
#include<lib/vv/sort.h>
#include<lib/nt.h>
#include<lib/nt/crt.h>
#include<lib/graph/functional_graph.h>

using namespace vv;

ll fmod(ll x, ll m) {
    return x >= m ? x - m : x;
}

void solve() {
    ll n; cin >> n;
    vl p(n); cin >> p; p = LC(x - 1, x, p);
    vl a(n); cin >> a;
    graph::FunctionalGraph fg(p);

    vb visited(n);

    vl output(n);
    vpl congs;
    FOR(i, 0, n - 1) {
        if (visited[i]) continue;
        ll cyc_number = fg.cycle_number[i];
        vl& cycle = fg.cycs[cyc_number];

        ll L = len(cycle);
        // dprint("Cycle of length", L);
        {
            ll idx = first_st(r, cycle[r] == i, 0, L - 1);
            std::rotate(cycle.begin(), cycle.begin() + idx, cycle.end());
        }
        vpl filtered_congs;
        foreach(pa, congs) {
            ll m = gcd(L, pa.second);
            filtered_congs.push_back({pa.first % m, m});
        }
        auto [res, m] = nt::crt(filtered_congs);
        assert(m > 0);
        assert(res < L);
        assert(res >= 0);

        pl best = {1e18, 1e18};
        SFOR(j, res, L - 1, m) {
            chkmin(best, pl{a[cycle[j]], j});
        }
        ll j = best.second;
        FOR(k, 0, L - 1) {
            output[cycle[k]] = a[cycle[fmod(k + j, L)]];
            visited[cycle[k]] = true;
        }
        congs.push_back({j, L});
    }
    print(output);
}

int main() {
    init();
    solve();
    return 0;
}