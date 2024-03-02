#pragma once

#include <lib/common.h>

/**
 * Description: Builds suffix array for a string.
 * \texttt{sa[i]} is the starting index of the suffix which
 * is $i$'th in the sorted suffix array.
 * The returned vector is of size $n+1$, and \texttt{sa[0] = n}.
 * The lcp array contains longest common prefixes for
 * neighbouring strings in the suffix array:
 * 
 *     lcp[i] = lcp(sa[i], sa[i-1]),
 *     lcp[0] = 0.
 * 
 * Time: O(n \log n)
 * Status: stress-tested
 * 
 * Usage: https://codeforces.com/contest/1923/submission/249026778
 * 
 * vi rbits(...);
 * SuffixArray sfx(rbits);
 * 
 * sfx.rank[x] // gets the rank (starting from 1) of the suffix starting at x -> $
 * 
 */

struct SuffixArray {
	vi sa, lcp;
    // idx = index in original array
    // rank = rank of the suffix starting from there.
    vi rank;

    /**
     * s may be either string or a vector<ll> or vector<int>.
     * Essentially, every s[i] needs to be able to be cast to int
     *
     * :param lim: The maximum value that the array s can take.
    */
    template <typename T>
	SuffixArray(const T& s_, int lim=255) {
        // We make a copy, because something about
        // this algorithm assumes that entries in s_ are positive
        vi s(ALL(s_));
        int mn = lim;
        walk(i, s_) chkmin(mn, s[i]);
        walk(i, s_) s[i] = s_[i] - mn + 1;
        lim = lim - mn + 1;
        s.pb(0); // Simulate a null char

        lim++;
        int n = len(s);
        int k = 0;
        int a, b;

        vi x(n); FOR(i, 0, n - 1) x[i] = s[i];
        vi y(n);
        vi ws(max(n, lim));
        rank.resize(n, 0);

		sa = lcp = y, iota(ALL(sa), 0); // sa is now 0, 1, 2, ..., n - 1

		for (int j = 0, p = 0; p < n; j = max(1, j * 2), lim = p) {
			p = j, iota(ALL(y), n - j);
			rep(i, 0, n) if (sa[i] >= j) y[p++] = sa[i] - j;

            // ws is the cumsum of the counts?
			fill(ALL(ws), 0);
			rep(i,0,n) ws[x[i]]++;
			rep(i,1,lim) ws[i] += ws[i - 1];

			for (int i = n; i--;) sa[--ws[x[y[i]]]] = y[i];
			swap(x, y), p = 1, x[sa[0]] = 0;
			rep(i,1,n) a = sa[i - 1], b = sa[i], x[b] =
				(y[a] == y[b] && y[a + j] == y[b + j]) ? p - 1 : p++;
		}
		rep(i,1,n) rank[sa[i]] = i;
		for (int i = 0, j; i < n - 1; lcp[rank[i++]] = k)
			for (k && k--, j = sa[rank[i] - 1];
					s[i + k] == s[j + k]; k++);
	}
};
