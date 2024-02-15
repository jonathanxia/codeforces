#include <lib/nt.h>

/**
 * Number of integers between 1 and u inclusive
 * that are relatively prime to x.
 * 
 * Requires prime factorization of x
*/
namespace nt {
    ll num_relatively_prime(ll x, ll u) {
        umapll ppp = primeFactorization(x);
        vl primes;
        foreachp(p, e, ppp) primes.pb(p);

        ll L = len(primes);
        ll fin = 0;
        FOR(mask, 0, (1LL << L) - 1)
        {
            ll pro = 1;
            ll sgn = 1;
            FOR(j, 0, L - 1) if (get_digit(mask, 2, j))
            {
                pro *= primes[j];
                sgn *= -1;
            }
            fin += u / pro * sgn;
        }

        return fin;
    }
} // namespace nt