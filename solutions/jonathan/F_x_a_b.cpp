// Link: https://atcoder.jp/contests/abc361/tasks/abc361_f
// Tests cpower and cmul

#include<lib/common.h>

void solve() {
    ll n; cin >> n;

    vl cnt(61);
    FOR(b, 2, 60) {
        ll u = largest_st(a, cpower(a, b) <= n, 0, n);
        // cnt[b] is number of b-th powers, excluding 1
        cnt[b] = u - 1;
    }
    ll tot = 0;
    DOR(i, 60, 2) {
        SFOR(j, 2 * i, 60, i) {
            cnt[i] -= cnt[j];
        }

        tot += cnt[i];
    }
    // Add back 1
    print(tot + 1);
}

int main() {
    init();
    solve();
    return 0;
}