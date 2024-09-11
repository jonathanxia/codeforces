// Link: https://codeforces.com/contest/2009/problem/F
#include <lib/vv/concat.h>
#include <lib/cum.h>
using namespace vv;

void solve() {
    ll n, q; cin >> n >> q;
    vl a(n); cin >> a;
    a = concat(a, a);
    cum::sum<ll> cs(a);

    cepeat(q) {
        ll l, r; cin >> l >> r; l--; r--;
        ll shift_l = l/n;
        ll pos_l = l % n;
        ll shift_r = r/n;
        ll pos_r = r % n;

        ll ans = (shift_r - shift_l - 1) * cs.query(0, n - 1);
        ans += cs.query(shift_l + pos_l, shift_l + n - 1);
        ans += cs.query(shift_r, shift_r + pos_r);
        print(ans);
    }
}

int main() {
    init();
    int t; cin >> t;
    cep(t) solve();
    return 0;
}