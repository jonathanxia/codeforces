// Link: https://atcoder.jp/contests/arc181/tasks/arc181_d
#include <lib/constants/mod998244353.h>
#include <lib/vv/sum.h>
#include <lib/vv/counter.h>
#include <lib/vv/sort.h>
#include <lib/fenwick.h>
#include <atcoder/lazysegtree>
#include <lib/algo/inversion.h>
/**
 * Sum segment tree that supports addition:
*/
struct S {
    ll data;
    ll sz;
};
S op(S l, S r) {
    return {l.data + r.data, l.sz + r.sz};
}
S e() { return S{0, 1}; }
using F = ll;
S mapping(F l, S r) {
    if (!l) return r;
    return {r.data + r.sz * l, r.sz};
}
F composition(F l, F r) { return l + r; }
F id() { return 0; }
// atcoder::lazy_segtree<S, op, e, F, mapping, composition, id> seg(a);
using namespace vv;

void solve() {
    ll n; cin >> n;
    vl a(n); cin >> a; a = LC(x - 1, x, a);
    vl val_to_idx(n); FOR(i, 0, n - 1) {
        val_to_idx[a[i]] = i;
    }

    vl num_bigger(n);
    FenwickTree<ll> ft(n);
    DOR(v, n - 1, 0) {
        ll i = val_to_idx[v];
        num_bigger[i] = ft.sum(0, i);
        ft.add(i, 1);
    }
    ll num_invs = algo::count_inversions(a);

    ll q; cin >> q;
    vl queries(q); cin >> queries; queries = LC(x - 1, x, queries);

    atcoder::lazy_segtree<S, op, e, F, mapping, composition, id> output(q);
    FOR(i, 0, n - 1) {
        ll qidx = smallest_st(j, queries[j] >= i, 0, q - 1);
        if (qidx == q) continue;
        ll end = min(qidx + num_bigger[i] - 1, q - 1);
        output.update(qidx, end, 1);
    }
    FOR(i, 0, q - 1) {
        print(num_invs - output.query(0, i).data);
    }
}

int main() {
    init();
    solve();
    return 0;
}