// Link: https://codeforces.com/contest/1989/problem/E
// Classic dp question
#include <lib/constants/mod998244353.h>
#include<lib/mod_int.h>
#include<lib/ndarray.h>
#include<lib/common.h>

void solve() {
    ll N, K; cin >> N >> K;
    ndarray<MI, 2> dp({N + 1, K + 1});
    ndarray<MI, 2> cdp({N + 1, K + 1});
    // Do the base case
    dp(0, 0) = 1;
    cdp(0, 0) = 1;
    FOR(n, 1, N) {
        dp(n, 0) = dp(n - 1, 0) + cdp(n - 3, 0);
        if (n == 2) dp(n, 0) += 1;
        cdp(n, 0) = cdp(n - 1, 0) + dp(n, 0);
    }

    FOR(k, 1, K) {
        FOR(n, k, N) {
            dp(n, k) = dp(n - 1, k - 1) + cdp(n - 3, k - 1);
            if (k == 1 && n == 2) {
                dp(n, k) += 1;
            }
        }
        FOR(n, k, N) {
            cdp(n, k) = cdp(n - 1, k) + dp(n, k);
        }
    }
    MI ans = 0;

    FOR(delta, 1, N - 1) {
        ans += dp(N - delta, K - 1);
    }

    print(ans);
}

int main() {
    init();
    solve();
    return 0;
}