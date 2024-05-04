#pragma once

#include <lib/fft.h>

/**
 * Computes the product of the polynomials
 * (1 + a[0] * x)(1 + a[1] * x) * ... * (1 + a[n - 1] * x)
 * in n log^2 n time
 * 
 * Usage: https://atcoder.jp/contests/abc352/submissions/53151117
 * 
*/
template <ll M = MOD>
vl binomial_prod_mod(const vector<ll>& a) {
    function<vl(ll, ll)> func = [&](ll start, ll end) {
        if (start == end) {
            return vl{1, a[start]};
        }
        if (start > end) {
            return vl{1};
        }

        ll mid = (start + end) / 2;
        vl left = func(start, mid);
        vl right = func(mid + 1, end);

        return fft::conv_mod(left, right);
    };
    return func(0, len(a) - 1);
}
