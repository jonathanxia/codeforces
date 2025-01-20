// Link: https://codeforces.com/contest/2061/problem/E
#include<lib/common.h>
#include<lib/vv/sum.h>
#include<lib/vv/sort.h>
#include<lib/bitster.h>
#include<lib/ndarray.h>

using namespace vv;

void solve() {
    ll n, m, k; cin >> n >> m >> k;
    vl a(n); cin >> a;
    vl b(m); cin >> b;
    ndarray<ll, 2> dp({n, m + 1}, 1e18);

    FOR(mask, 0, (1LL << m) - 1) {
        ll num = 0;
        ll res = (1LL << 30) - 1;
        FOR(j, 0, m - 1) if (bitster::get_bit(mask, j)) {
            num++; res &= b[j];
        }

        FOR(i, 0, n - 1) chkmin(dp(i, num), res & a[i]);
    }

    vl delta;
    FOR(i, 0, n - 1) FOR(j, 0, m - 1) {
        delta.pb(dp(i, j) - dp(i, j + 1));
    }
    rsort(delta);
    ll decrease = k == 0 ? 0 : sum(delta, 0, k - 1);
    print(sum(a) - decrease);
}

int main() {
    init();
    int t; cin >> t;
    cep(t) solve();
    return 0;
}