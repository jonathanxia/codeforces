#pragma once
#include <lib/nt.h>

namespace nt {
    /**
     * A datastructure that performs a sieve up to a certain number to
     * figure out the smallest prime divisor of a number.
     * 
     * Precompute time is O(N log(log(N)))
     */
    template <int N=1'000'000>
    struct SmallestPrimeDiv {
        array<ll, N + 1> smallest_div;
        SmallestPrimeDiv() {
            FOR(p, 2, N) {
                if (smallest_div[p] > 0) continue;
                // p is prime at this point
                SFOR(kp, p, N, p) if (smallest_div[kp] == 0) {
                    smallest_div[kp] = p;
                }
            }
            smallest_div[0] = 0;
            smallest_div[1] = 1;
        }

        /**
         * Smallest prime divisor of x
         */
        ll query(ll x) {
            assert(x <= N);
            assert(x >= 0);
            return smallest_div[x];
        }
    };
};