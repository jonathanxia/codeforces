// Link: https://codeforces.com/contest/1999/problem/E
#include <lib/common.h>

void solve() {
    ll l, r; cin >> l >> r;    
    vl counts(14);
    FOR(i, 0, 13) {
        // Has i digits
        // Between < 3^(i + 1)
        ll left = max(l, power(3, i));
        ll right = min(r, power(3, i + 1) - 1);
        if (left > right) continue;
        counts[i] = right - left + 1;
    }
    ll sm = first_st(i, counts[i] > 0, 0, 13);
    ll ans = sm + 1;
    FOR(i, 0, 13) {
        ans += (i + 1) * counts[i];
    }
    print(ans);
}

int main() {
    init();
    int t; cin >> t;
    cep(t) solve();
    return 0;
}