#include <lib/common.h>

// Solves subset sum when the items are nonnegative.
// Complexity: O(target * len(items))
template <int L = 1>
bool subset_sum(const vl& items, int target)
{
    if (target >= L) {
        return subset_sum<min(2 * L, 1000000)>(items, target);
    }

    bitset<L> dp;

    dp[0] = 1;
    for (ll x : items) {
        dp = dp | (dp << x);
    }

    return dp[target];
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
