// Link: https://codeforces.com/contest/1993/problem/C
#include <lib/constants/mod998244353.h>
#include <lib/vv/sum.h>
#include <lib/vv/counter.h>
#include <lib/vv/sort.h>
#include <atcoder/lazysegtree>
using namespace vv;
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

void solve() {
    ll n, k; cin >> n >> k;
    vl a(n); cin >> a;
    sort(a);

    atcoder::lazy_segtree<S, op, e, F, mapping, composition, id> seg(2 * k);
    FOR(i, 0, n - 1) {
        ll start = mod(a[i] - a[n - 1], 2 * k);
        seg.circular_update(start, start + k - 1, 1);
    }
    ll offset = first_st(i, seg.query(i, i).data == n, 0, 2 * k - 1);
    if (offset == 2 * k) {
        print(-1);
    }
    else {
        print(a[n - 1] + offset);
    }
}

int main() {
    init();
    int t; cin >> t;
    cep(t) solve();
    return 0;
}