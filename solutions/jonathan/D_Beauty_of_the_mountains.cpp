// Link: https://codeforces.com/contest/1982/problem/D
#include <lib/vv.h>
#include <lib/datastruct/ndarray.h>
#include <lib/cum2d.h>
using namespace vv;

void solve() {
    ll n, m, k; cin >> n >> m >> k;
    ndarray<ll, 2> a({n, m});
    ndarray<ll, 2> is_snow({n, m});
    cin >> a;
    FOR(i, 0, n - 1) FOR(j, 0, m - 1) {
        char ch; cin >> ch;
        if (ch == '1') is_snow(i, j) = 1;
        else is_snow(i, j) = -1;
    }
    ll tot = 0;
    FOR(i, 0, n - 1) FOR(j, 0, m - 1) {
        tot += a(i, j) * is_snow(i, j);
    }

    // Gather the submasks
    vvl is_snow_(n, vl(m)); FOR(i, 0, n - 1) FOR(j, 0, m - 1) is_snow_[i][j] = is_snow(i, j);
    CumSum2d<ll> cs(is_snow_);
    set<ll> coeffs;
    FOR(i, 0, n - k) FOR(j, 0, m - k) {
        coeffs.insert(cs.query(i, i + k - 1, j, j + k - 1));
    }
    dbg(coeffs);
    ll g = 0;
    foreach(c, coeffs) g = gcd(g, c);
    dprint("Target tot=", tot, "gcd=", g);
    print(mod(tot, g) == 0 ? "YES":"NO");
}

int main() {
    init();
    int t; cin >> t;
    cep(t) solve();
    return 0;
}