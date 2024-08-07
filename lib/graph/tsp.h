#include <lib/common.h>
#include <lib/ndarray.h>
#include <lib/bitster.h>

// Solves the travelling salesman problem
// One needs to provide an n x n matrix of costs
// Doesn't really matter what you place on the diagonal though
// Runtime: O(n^2 * 2^n)

namespace graph {
ndarray<ll, 2> tsp_with_dp(ndarray<ll, 2>& w) {
    // The travelling salesman dp
    // Simply do a bitset dp on this
    ll n = w.dimensions[0];
    assert(w.dimensions[1] == n);

    ll MX = (1LL << n) - 1;
    ndarray<ll, 2> dp({n, MX + 1}, 1e18); // last, mask
    // Let's do pull dp, set the initial states
    FOR(i, 0, n - 1) {
        dp(i, 1LL << i) = 0;
    }
    FOR(mask, 0, MX) {
        if (__builtin_popcountl(mask) <= 1) continue;
        FOR(last, 0, n - 1) {
            if (bitster::get_bit(mask, last) == 0) continue;
            ll new_mask = mask ^ (1LL << last);
            // Now iterate over each bit of new_mask for the last guy
            FOR(b, 0, n - 1) if (bitster::get_bit(new_mask, b)) {
                chkmin(dp(last, mask), dp(b, new_mask) + w(b, last));
            }
        }
    }
    return dp;
}

ll tsp(ndarray<ll, 2>& w) {
    // The travelling salesman dp
    // Simply do a bitset dp on this
    ll n = w.dimensions[0];
    assert(w.dimensions[1] == n);
    ll MX = (1LL << n) - 1;
    auto dp = tsp_with_dp(w);

    ll ans = 1e18;
    FOR(last, 0, n - 1) {
        chkmin(ans, dp(last, MX));
    }
    return ans;
}
} //namespace graph