#pragma once

#include <lib/nt.h>

namespace nt_crt {
    /**
     * Checks if the congruence
     * x = a (mod m)
     * y = b (mod n)
     * 
     * is feasible or not
    */
    template <typename T=ll>
    bool check_possible(T a, T m, T b, T n) {
        T g = gcd(m, n);
        return a % g == b % g;
    }

    template <typename T=ll, bool CHECK_POSSIBLE=true>
    pair<T, T> crt(T a, T m, T b, T n) {
        chkmod(a, m);
        chkmod(b, n);
        if (CHECK_POSSIBLE && !check_possible(a, m, b, n)) return {-1, -1};
        T g = gcd(m, n);
        n /= g;
        b = b % n;

        T y = nt::inv<T>(m, n) * (b - a);
        y = y % n;

        T p = m * n;
        return  {mod(m * y + a, p), p};
    }

    /**
     * Computes the solution to
     * x = ai (mod mi)
     * 
     * where congruences = { (a1, m1), (a2, m2), ... }
    */
    template <typename T=ll, bool CHECK_POSSIBLE=true>
    pair<T, T> crt(vector<pair<T, T>> congruences) {
        if (len(congruences) == 0) return {0, 1};
        if (len(congruences) == 1) return congruences[0];
        pair<T, T> ret = congruences[0];
        FOR(i, 1, len(congruences) - 1) {
            ret = crt<T, CHECK_POSSIBLE>(ret.first, ret.second, congruences[i].first, congruences[i].second);
            // Check if impossible
            if (CHECK_POSSIBLE) {
                if (ret.second == -1) return ret;
            }
        }
        return ret;
    }
} // namespace nt_crt

using nt_crt::crt;