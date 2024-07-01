// Link: https://codeforces.com/contest/1987/problem/F2
#include <lib/common.h>
#include<lib/datastruct/ndarray.h>

void solve() {
    ll n; cin >> n; vl a(n); cin >> a;
    FOR(i, 0, n - 1) a[i] = i + 1 - a[i];

    if (all_st(i, a[i] != 0, 0, n - 1)) {
        print(0); return;
    }

    ndarray<ll, 2> dp({n, n}, -2); // [left, right]
    function<ll(ll, ll)> func = [&](ll left, ll right) {
        if (left > right) return 0LL;
        if (dp(left, right) != -2) return dp(left, right);

        if (mod(right - left, 2) != 1) {
            return dp(left, right) = 1e18;
        }
        if (a[left] < 0 || a[left] % 2 != 0) {
            return dp(left, right) = 1e18;
        }
        if (right - left == 1) {
            return dp(left, right) = a[left] / 2;
        }
        // Left is going to go with right
        ll ret = 1e18;
        SFOR(mid, left + 1, right, 2) {
            // Kill from left to mid
            ll middle_cost = func(left + 1, mid - 1);
            if (a[left] / 2 < middle_cost) continue;

            ll ans = a[left] / 2;

            // Also need to kill from mid + 1 to right
            ll right_ans = func(mid + 1, right);

            ans = max(ans, right_ans - (mid - left + 1) / 2);
            chkmin(ret, ans);
        }
        return dp(left, right) = ret;
    };

    ndarray<ll, 1> fdp({n}, 0);

    FOR(i, 1, n - 1) {
        chkmax(fdp(i), fdp(i - 1));
        FOR(j, 0, i - 1) {
            if (func(j, i) <= fdp(j - 1))
                chkmax(fdp(i), fdp(j - 1) + (i - j + 1) / 2);
        }
    }
    print(fdp(n - 1));
}

int main() {
    init();
    int t; cin >> t;
    cep(t) solve();
    return 0;
}