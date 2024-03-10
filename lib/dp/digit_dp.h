#pragma once
#include <lib/common.h>

/**
 * NOTE: this is not a standalone function. It serves more as a template or example
 * for a digit dp question so you can modify accordingly.
 * 
 * Full submission and problem statement: https://atcoder.jp/contests/arc173/submissions/51144666
 * 
 * The code below calculates for how many numbers <= x are there such that no two consecutive digits
 * are equal.
*/

void solve() {
    ll k; cin >> k;

    // Global state for the upper bound to the dp. This must be reset every
    // time if the upper bound changes.
    //
    // Tip: Do not call func() directly, rather call rfunc which takes care of
    // reinitialization
    string s;
    umap<array4, ll> dp;

    function<ll(ll, ll, ll, ll)> func = [&](ll pos, ll pre_digit, ll under, ll started) {
        // Check for precomputation ----------------------------
        array4 params {pos, pre_digit, under, started};
        if (dp.count(params)) return dp[params];

        // Handle base cases here -------------------------------
        if (pos == len(s)) {
            return dp[params] = started;
        }

        if (under) {
            // We can pick any digit we want, though note that we
            // have not necessarily started yet
            ll ans = 0;
            FOR(i, 0, 9) {
                // Transition logic here ---------------------------
                if (started && i == pre_digit) continue;
                ans += func(pos + 1, i, 1LL, started || (i > 0));
            }
            return dp[params] = ans;
        }
        else {
            // Can only go up to the digit of the number
            ll ans = 0;
            ll digit = s[pos] - '0';
            FOR(i, 0, digit) {
                // Transition logic here ---------------------------
                if (started && i == pre_digit) continue;
                ans += func(pos + 1, i, i < digit, started || (i > 0));
            }
            return dp[params] = ans;
        }
    };

    function<ll(ll)> rfunc = [&](ll guess) {
        s = to_str(guess);
        dp.clear();
        return func(0, 20, false, false);
    };

    // Answer extraction, problem dependent ---------------------
    ll ans = smallest_st(x, rfunc(x) >= k, 0, ll(1e18));
    print(ans);
}
