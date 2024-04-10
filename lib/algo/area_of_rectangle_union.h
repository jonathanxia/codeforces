#pragma once
#include <lib/common.h>
#include <atcoder/lazysegtree>

/**
 * Computes the area of the union of a bunch of rectangles.
 * Runtime is O(N log N) where N is the number of rectangles
 * 
 * Usage:
int main() {
	int n;
	scanf("%d", &n);
	vector<int> l(n), r(n), d(n), u(n);
	for (int i = 0; i < n; ++i) {
		scanf("%d%d%d%d", &l[i], &d[i], &r[i], &u[i]);
	}
	printf("%lld\n", union_of_rectangles(l, r, d, u));
}
*/
namespace structures {
	struct S {
		int val, cnt;

		static S op(S x, S y) {
			if (x.val != y.val) return (x.val < y.val ? x : y);
			else return { x.val, x.cnt + y.cnt };
		}
		static S e() { return { 1000'000'000, 0 }; }
	};
	struct F {
		int add;

		static S mapping(F f, S x) { return { x.val + f.add, x.cnt }; }
		static F composition(F f, F g) { return { g.add + f.add }; }
		static F id() { return { 0 }; }
	};
}
long long union_of_rectangles(vector<int> ls, vector<int> rs, vector<int> ds, vector<int> us) {
	using namespace structures;
    using namespace atcoder;

	const int n = ls.size();
	vector<int> xs(2 * n), ys(2 * n);
	copy(ls.begin(), ls.end(), xs.begin()); copy(rs.begin(), rs.end(), xs.begin() + n);
	copy(ds.begin(), ds.end(), ys.begin()); copy(us.begin(), us.end(), ys.begin() + n);
	sort(xs.begin(), xs.end()); sort(ys.begin(), ys.end());
	xs.erase(unique(xs.begin(), xs.end()), xs.end()); ys.erase(unique(ys.begin(), ys.end()), ys.end());

	const int m = xs.size(), w = ys.size();

	vector<int> l1 = ls, r1 = rs, d1 = ds, u1 = us;
	for (auto& e : l1) e = lower_bound(xs.begin(), xs.end(), e) - xs.begin();
	for (auto& e : r1) e = lower_bound(xs.begin(), xs.end(), e) - xs.begin();
	for (auto& e : d1) e = lower_bound(ys.begin(), ys.end(), e) - ys.begin();
	for (auto& e : u1) e = lower_bound(ys.begin(), ys.end(), e) - ys.begin();

	vector<vector<pair<int, pair<int, int>>>> lr(w);
	{
		vector<int> siz(w);
		for (int i = 0; i < n; ++i) siz[d1[i]]++, siz[u1[i]]++;
		for (int i = 0; i < w; ++i) lr[i].reserve(siz[i]);
	}
	for (int i = 0; i < n; ++i) {
		lr[d1[i]].emplace_back(1, make_pair(l1[i], r1[i]));
		lr[u1[i]].emplace_back(-1, make_pair(l1[i], r1[i]));
	}
	
	lazy_segtree<S, S::op, S::e, F, F::mapping, F::composition, F::id> seg(m);
	for (int i = 0; i < m - 1; ++i) seg.set(i, S{ 0, xs[i + 1] - xs[i] });

	long long res = 0;
	for (int i = 0; i < w - 1; ++i) {
		for (auto [k, p] : lr[i]) seg.apply(p.first, p.second, F{ k });

		auto [val, cnt] = seg.all_prod();
		long long tmp = (xs[m - 1] - xs[0]) - (val == 0 ? cnt : 0);
		res += tmp * (ys[i + 1] - ys[i]);
	}
	return res;
}
