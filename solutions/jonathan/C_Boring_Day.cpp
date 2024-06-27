// Link: https://codeforces.com/contest/1982/problem/C
#include <lib/vv.h>
#include <lib/cum.h>
using namespace vv;

void solve() {
    ll n; ll l, r; cin >> n >> l >> r;
    vl a(n); cin >> a;
    cum::sum<ll> cs(a);
    ll li = 0;
    ll ri = 0;
    ll ans = 0;
    while (ri <= n) {
        // Check if this works
        ll z = cs.query(li, ri);
        if (ordered(l, z, r)) {
            ans++;
            ri++;
            li = ri;
            continue;
        }
        // Otherwise z does not work
        if (z < l) {
            ri++;
            continue;
        }
        if (z > r) {
            li++;
            continue;
        }
    }
    print(ans);
}

int main() {
    init();
    int t; cin >> t;
    cep(t) solve();
    return 0;
}