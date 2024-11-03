#include <lib/bitster.h>

namespace bitster
{
    // computes 1 ^ 2 ^ 3 ^ ... ^ num in constant time
    ll prefix_xor(ll num) {
        // Key observation, every four numbers are 0 XOR, so we only look
        // at it mod 4.
        ll ans = 0;
        if ((num & 1) == 0) ans |= ((num >> 2) << 2);
        ll rem = num & 3; // Take this number (mod 4)
        if (rem == 0 || rem == 3) return ans;
        if (rem == 1) return ans | 1;
        if (rem == 2) return ans | 3;
        return 0;
    }
} // namespace bitster