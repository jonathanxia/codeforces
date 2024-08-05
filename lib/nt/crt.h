#pragma once

#include <lib/nt.h>

namespace nt {
    /**
     * Solves a linear congruence of the form ax = b (mod m)
     * 
     * Returns the solution c (mod n) where n is some divisor of m,
     * if it is possible to have a solution.
     * 
     * Otherwise, it returns (-1, -1)
     */
    template <typename T=ll, bool CHECK_POSSIBLE=true>
    pair<T, T> solve_linear(T a, T b, T m) {
        chkmod(a, m); chkmod(b, m);
        T g = gcd(a, m);
        if (CHECK_POSSIBLE && mod(b, g) != 0) {
            return {-1, -1};
        }
        // Now it is possible, remove common factors
        a /= g; b /= g; m /= g;
        return {nt::mdiv(b, a, m), m};
    }
} // namespace nt


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
        // Solve the equation x = t * m + a
        // t * m + a = b (mod n)
        // t * m = b - a (mod n) <-- Solve this for t
        auto [c, p] = nt::solve_linear(m, b - a, n);
        // Now we get t = c (mod p)
        // so then x = t * m + a = (ps + c) * m + a
        // x = s * (mp) + c * m + a
        pair<T, T> res;
        res.second = m * p;
        res.first = mod(c * m + a, res.second);

        return res;
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

namespace nt {
    using nt_crt::crt;
}

