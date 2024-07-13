// Link: https://atcoder.jp/contests/abc352/tasks/abc352_g
#include <lib/constants/mod998244353.h>
#include <lib/algo/binomial_prod.h>
#include <lib/nt.h>
#include <lib/ndarray.h>
#include <lib/mod_int.h>

void solve() {
    ll n; cin >> n; vl a(n); cin >> a;
    MI s = 0;
    foreach(x, a) s += x;
    MI ans = 1;
    MI denom = 1;
    vl tots = binomial_prod_mod(a);
    // dbg(tots);

    FOR(k, 1, n) {
        // Answer is > k so we need
        denom *= (s - k + 1);
        ans += MI(tots[k]) / denom * combo::factorial[k];
    }
    print(ans);
    // dprint(ans.as_frac());
    // dprint(MI(665496238).as_frac());
}

int main() {
    combo::precompute_fac(300002);
    init();
    solve();
    return 0;
}