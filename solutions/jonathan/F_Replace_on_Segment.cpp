// Link: https://codeforces.com/contest/1922/problem/F
#include<lib/ndarray.h>
#include<lib/common.h>

void solve() {
    ll n, x; cin >> n >> x;
    vl a(n); cin >> a;
    ndarray<ll, 3> dp({n, n, x + 1}, 1e18);
    ndarray<ll, 3> dp2({n, n, x + 1}, 1e18);

    // width = 1
    FOR(L, 0, n - 1) {
        FOR(t, 1, x) {
            dp(L, L, t) = a[L] != t ? 1 : 0;
            dp2(L, L, t) = a[L] == t ? 1 : 0;
        }
    }
    FOR(L, 0, n - 2) {
        FOR(t, 1, x) {
            dp(L, L + 1, t) = (a[L] == t && a[L + 1] == t) ? 0 : 1;
            if (a[L] != t && a[L + 1] != t) {
                dp2(L, L + 1, t) = 0;
            }
            else {
                dp2(L, L + 1, t) = 1;
            }
        }
    }

    function<ll(ll, ll, ll)> f;
    function<ll(ll, ll, ll)> g;

    f = [&](ll l, ll r, ll t) {
        if (dp(l, r, t) != 1e18) {
            return dp(l, r, t);
        }

        if (a[l] == t || a[l + 1] != t) {
            return dp(l, r, t) = f(l + 1, r, t);
        }
        if (a[r] == t || a[r - 1] != t) {
            return dp(l, r, t) = f(l, r - 1, t);
        }

        // Flip L
        ll ans = 1e18;
        ll L = l;
        ll R = r;
        chkmin(ans, f(L + 1, R, t) + 1);
        chkmin(ans, f(L, R - 1, t) + 1);
        // L + 1 through R - 1
        chkmin(ans, g(L + 1, R - 1, t) + 1);
        return dp(L, R, t) = ans;
    };

    g = [&](ll l, ll r, ll t) {
        if (dp2(l, r, t) != 1e18) {
            return dp2(l, r, t);
        }

        if (a[l] != t) {
            return dp2(l, r, t) = g(l + 1, r, t);
        }
        if (a[r] != t) {
            return dp2(l, r, t) = g(l, r - 1, t);
        }

        ll ans = 1e18;
        FOR(m, 1, x) if (m != t) {
            chkmin(ans, f(l, r, m));
        }

        FOR(mid, l, r - 1) {
            chkmin(ans, g(l, mid, t) + g(mid + 1, r, t));
        }
        return dp2(l, r, t) = ans;
    };

    ll ans = 1e18;
    FOR(t, 1, x) {
        chkmin(ans, f(0, n - 1, t));
    }
    print(ans);
}

int main() {
    init();
    int t; cin >> t;
    cep(t) solve();
    return 0;
}