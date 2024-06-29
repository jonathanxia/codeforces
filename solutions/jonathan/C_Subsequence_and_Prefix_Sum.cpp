// Link: https://atcoder.jp/contests/arc180/tasks/arc180_c
#include<lib/common.h>
#include<lib/macros.h>
#include<lib/mod_int.h>
#include<lib/inp.h>
#include<lib/print.h>
#include<lib/datastruct/ndarray.h>
#include<lib/nt.h>
#include<lib/vv.h>
using namespace vv;

void solve() {
    using MI = ModInt<1'000'000'007LL>;
    ll n; cin >> n;
    vl a(n + 1); inp::read1(a);

    // (i, c, active) = position i is "used" and has cumsum of c and if active
    ll MX = 0; foreach(x, a) chkmax(MX, abs(x));
    ndarray<MI, 3> dp({0, -MX * n, 0}, {n, MX * n, 1});
    // Base case
    dp(0, 0, 1) = 1;

    FOR(i, 0, n - 1) {
        FOR(c, -MX * i, MX * i) {
            // Calculate all places it can go
            if (dp(i, c, 0) == 0 && dp(i, c, 1) == 0) continue;
            if (c != 0) {
                dp(i + 1, c, 0) += dp(i, c, 1);
                dp(i + 1, c + a[i + 1], 1) += dp(i, c, 1);

                dp(i + 1, c, 0) += dp(i, c, 0);
                dp(i + 1, c + a[i + 1], 1) += dp(i, c, 0);
            }
            else {
                set<ll> seen; seen.insert(0);
                FOR(j, i + 1, n) {
                    if (seen.count(a[j])) continue;
                    dp(j, a[j], 0) += dp(i, 0, 1);
                    seen.insert(a[j]);
                }
            }
        }
    }

    MI ans = 0;
    FOR(i, 0, n) {
        FOR(c, -MX * n, MX * n) {
            ans += dp(i, c, 1);
        }
    }
    print(ans);
}

int main() {
    init();
    solve();
    return 0;
}