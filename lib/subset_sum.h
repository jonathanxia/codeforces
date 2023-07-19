#include "common.h"

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
