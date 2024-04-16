#pragma once

/**
 * Computes the prime factorization of a number n is worst cast
 * n^(1/4) time. This allows us to factor numbers up to 10^18,
 * the largest long long size.
 *
 * The main function is pollard::primeFactorize(n) which mimics
 * the interface to nt::primeFactorize.
 *
 * It requires the nt::do_sieve(200000) function to be run though.
*/
#include <lib/nt.h>

namespace pollard {
    typedef unsigned long long ull;
    ull modmul(ull a, ull b, ull M) {
        return (__int128_t) a * b % M;
    }
    ull modpow(ull b, ull e, ull mod) {
        ull ans = 1;
        for (; e; b = modmul(b, b, mod), e /= 2)
            if (e & 1) ans = modmul(ans, b, mod);
        return ans;
    }

    bool isPrime(ull n) {
        if (n < 2 || n % 6 % 4 != 1) return (n | 1) == 3;
        ull A[] = {2, 325, 9375, 28178, 450775, 9780504, 1795265022},
            s = __builtin_ctzll(n-1), d = n >> s;
        for (ull a : A) {   // ^ count trailing zeroes
            ull p = modpow(a%n, d, n), i = s;
            while (p != 1 && p != n - 1 && a % n && i--)
                p = modmul(p, p, n);
            if (p != n-1 && i != s) return 0;
        }
        return 1;
    }

    ll pollard_rho(ll n, ll seed) {
        if (n == 1) return n;
        if (n % 2 == 0) return 2;

        ll x = seed; // Start with a fixed value for x
        ll y = seed;
        ll d = 1;

        auto f = [&n](ll x1) {
            ll res = modmul(x1, x1, n) + 1;
            if (res >= n) return res - n;
            return res;
        };

        while (d == 1) {
            x = f(x);
            y = f(f(y));
            d = std::gcd(std::abs(x - y), n);
        }
        return d;
    }

    void _prime_factorize(ll n, umapll& res) {
        // Check primality of n
        if (n <= 1) return;
        if (n <= 2) { res[2]++; return; }

        if (n < len(nt::is_composite)) {
            ll d = nt::is_composite[n];
            if (d == 0) {
                res[n]++; return;
            }
            else {
                res[d]++;
                _prime_factorize(n / d, res);
                return;
            }
        }

        // Are we sure that n is prime? Use primality check
        if (isPrime(n)) {
            res[n]++; return;
        }
        // We are guaranteed a divisor, so use pollard
        ll d;
        do {
            d = pollard_rho(n, uid(2, n - 3));
        } while (d == n || d == 1);
        _prime_factorize(d, res);
        _prime_factorize(n / d, res);
    }

    umapll primeFactorize(ll n) {
        assert(nt::sieve_done);

        umapll ret;
        _prime_factorize(n, ret);
        return ret;
    }
} // namespace pollard
