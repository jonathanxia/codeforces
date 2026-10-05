#pragma once
#include <lib/common.h>

// Solves subset sum when the items are nonnegative.
// Complexity: O(target * len(items))
// max_reachable must be below SUBSET_SUM_MAX_L
const int SUBSET_SUM_MAX_L = 1 << 24;
template <int L = 1>
vector<bool> subset_sum(const vi& items, int max_reachable)
{
    if constexpr (L < SUBSET_SUM_MAX_L) {
        if (max_reachable >= L)
            return subset_sum<2 * L>(items, max_reachable);
    }
    assert(max_reachable < L);

    // static: a large bitset would overflow the stack
    static bitset<L> dp, tmp;
    dp.reset();
    dp[0] = 1;
    for (int x : items) {
        tmp = dp;
        tmp <<= x;
        dp |= tmp;
    }

    // Copy over to vector<bool> so we can actually return something
    vector<bool> result(dp.size());
    rep(i, 0, len(result))
        result[i] = dp[i];
    return result;
}

/*
* Actually provides which subset will achieve the target sum
*/
bool slow_subset_sum_with_sol(const vl& items, ll target, vb& marked) {
    ll m = len(items);
    ll tot = 0;
    FOR(i, 0, m - 1) tot += items[i];
    marked.resize(m);
    FOR(i, 0, m - 1) marked[i] = false;

    if (target > tot) return false;

    vector<vb> dp(tot + 1, vb(m + 1));
    dp[0][0] = true;

    FOR(j, 1, m) {
        FOR(s, 0, tot) {
            dp[s][j] = dp[s][j - 1];
            if (items[j - 1] <= s) {
                dp[s][j] = dp[s][j] || dp[s - items[j - 1]][j - 1];
            }
        }
    }

    if (!dp[target][m]) return false;

    DOR(j, m, 1) {
        ll elem = items[j - 1];
        if (elem <= target && dp[target - elem][j - 1]) {
            target -= elem;
            marked[j - 1] = true;
        }
    }

    return true;
}
