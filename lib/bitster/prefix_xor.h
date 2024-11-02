#include <lib/bitster.h>

namespace bitster
{
    // computes 1 ^ 2 ^ 3 ^ ... ^ num in constant time
    ll prefix_xor(ll num)
    {
        ll prefix = 0;
        rep(i, 0, 62)
        {
            ll mask = 1LL << i;
            if (i == 0) {
                // special case
                ll mod4 = num & 0b11;
                if (mod4 == 1 || mod4 == 2) {
                    prefix |= mask;
                }
            } else {
                ll mod = num & ((mask << 1) - 1);
                if (mod >= mask && !((mod - mask) & 1)) {
                    prefix |= mask;
                }
            }
        }
        return prefix;
    }
} // namespace bitster