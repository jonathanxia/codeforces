#pragma once
#include <lib/common.h>

namespace kmp {
// Returns the pi, where pi[x] is the longest proper prefix of s[0...x]
// that is also a suffix.
vi pi(const string& s)
{
    vi p(len(s));
    rep(i, 1, len(s))
    {
        int g = p[i - 1];
        while (g && s[i] != s[g])
            g = p[g - 1];
        p[i] = g + (s[i] == s[g]);
    }
    return p;
}

// Returns the indices that where pat is a substring of s.
vi match(const string& s, const string& pat)
{
    vi p = pi(pat + '\0' + s), res;
    rep(i, len(p) - len(s), len(p))
    {
        if (p[i] == len(pat))
            res.push_back(i - 2 * len(pat));
    }
    return res;
}
}