#pragma once

// Just use atcoder's interface, it is nice
#include <atcoder/string>
#include <lib/vv.h>
#include <lib/str.h>

/**
 * Computes the longest suffix of s1 that is also a prefix of s2
 *
 * Essentially, if you try to jam s1 + s2 together, how much can you compress it
 * Runtime: O(min(len(s1), len(s2)))
 *
 * Usage: https://atcoder.jp/contests/abc343/submissions/50855658
 * https://codeforces.com/contest/1200/submission/250020937
*/
ll longest_suffix_prefix(const string& s1, const string& s2) {
    // We should take the min of these two strings, so that
    // we can maintain the run time of O(min(len(s1), len(s2)))
    ll L = min(len(s1), len(s2));
    if (L == 0) return 0;
    string s = str::slc(s2, 0, L - 1) + "~" + str::slc(s1, len(s1) - L, len(s1) - 1); // ~ is a very large char
    vi z = atcoder::z_algorithm(s);

    ll idx1 = L + 1;
    FOR(i, idx1, len(s) - 1) {
        // Check if this is a suffix
        if (z[i] == len(s) - i) return z[i];
    }
    return 0;
}