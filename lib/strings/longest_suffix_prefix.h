#pragma once

// Just use atcoder's interface, it is nice
#include <atcoder/string>
#include <lib/vv.h>

/**
 * Computes the longest suffix of s1 that is also a prefix of s2
 * 
 * Essentially, if you try to jam s1 + s2 together, how much can you compress it
 * Runtime: O(len(s1) + len(s2))
 * 
 * Usage: https://atcoder.jp/contests/abc343/submissions/50855658
*/
ll longest_suffix_prefix(string s1, string s2) {
    string s = s2 + "~" + s1; // ~ is a very large char
    vi z = atcoder::z_algorithm(s);

    ll idx1 = len(s2) + 1;
    FOR(i, idx1, len(s) - 1) {
        // Check if this is a suffix
        if (z[i] == len(s) - i) return z[i];
    }
    return 0;
}