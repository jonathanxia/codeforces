#pragma once
/**
 * Author: Johan Sannemo
 * License: CC0
 * Description: Compute indices of smallest set of intervals covering another interval.
 * Intervals should be [inclusive, exclusive). To support [inclusive, inclusive],
 * change (A) to add \texttt{|| R.empty()}. Returns empty set on failure (or if G is empty).
 * Time: O(N \log N)
 * Status: Tested on kattis:intervalcover
 */
#include <lib/common.h>

namespace kactl {
template<class T>
vi cover(pair<T, T> G, vector<pair<T, T>> I) {
	vi S(len(I)), R;
	iota(ALL(S), 0);
	sort(ALL(S), [&](int a, int b) { return I[a] < I[b]; });
	T cur = G.first;
	int at = 0;
	while (cur < G.second) { // (A)
		pair<T, int> mx = make_pair(cur, -1);
		while (at < len(I) && I[S[at]].first <= cur) {
			mx = max(mx, make_pair(I[S[at]].second, S[at]));
			at++;
		}
		if (mx.second == -1) return {};
		cur = mx.first;
		R.push_back(mx.second);
	}
	return R;
}
}