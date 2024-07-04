// Link: https://atcoder.jp/contests/arc180/tasks/arc180_d
#include<atcoder/lazysegtree.hpp>
#include<atcoder/internal_bit.hpp>
#include<atcoder/lazysegtree>
#include<atcoder/internal_bit>
#include<lib/macros.h>
#include<lib/print.h>
#include<lib/vv/sort.h>
#include <lib/vv/with_idx.h>
#include<lib/inp.h>
#include<lib/common.h>
#include<lib/sparsetable.h>

using namespace vv;

/**
 * Max segment tree that supports addition:
*/
using S = ll;
S op(S l, S r) {
    return min(l, r);
}
S e() { return ll(1e10); }
using F = ll;
S mapping(F l, S r) {
    if (!l) return r;
    return l + r;
}
F composition(F l, F r) { return l + r; }
F id() { return 0; }
// atcoder::lazy_segtree<S, op, e, F, mapping, composition, id> seg(a);

void solve() {
    ll n, q; cin >> n >> q;
    vl a(n); cin >> a;
    vl output(q, 1e18);
    vector<array3> queries(q);
    FOR(qi, 0, q - 1) {
        ll L, R; cin >> L >> R;
        L--; R--;
        queries[qi] = {L, R, qi};
    }

    auto func = [&]() {
        rsort(queries);
        atcoder::lazy_segtree<S, op, e, F, mapping, composition, id> seg(a);
        SparseTable<pl> sparse(with_idx(a), [](pl x, pl y) { return max(x, y); });
        vpl stk; stk.push_back({1e18, n - 1});
        set<ll> visited;
        visited.insert(n);

        foreach(query, queries) {
            ll qi = query[2];
            ll L = query[0];
            ll R = query[1];

            // Do basic diligence
            chkmin(output[qi], a[L] + a[R] + sparse.query(L + 1, R - 1).first);
            chkmin(output[qi], a[L] + a[L + 1] + sparse.query(L + 2, R).first);

            // Update data structures
            ll last_seen = *visited.begin();
            DOR(Li, last_seen - 1, L) {
                while (stk.back().first < a[Li]) {
                    ll j = stk.back().second;
                    stk.pop_back();
                    ll j2 = stk.back().second;
                    seg.update(j + 1, j2, -a[j]);
                }
                seg.update(Li + 1, stk.back().second, a[Li]);
                stk.push_back({a[Li], Li});
                visited.insert(Li);
            }

            // Assume it eats the right
            ll idx = sparse.query(L, R).second;
            if (idx >= L + 2) {
                chkmin(output[qi], a[idx] + seg.query(L + 1, idx - 1));
            }
        }
    };
    func();
    reverse(ALL(a));
    walk(i, queries) {
        queries[i][0] = n - 1 - queries[i][0];
        queries[i][1] = n - 1 - queries[i][1];
        swap(queries[i][0], queries[i][1]);
    }
    func();
    foreach(elem, output) print(elem);
}

int main() {
    init();
    solve();
    return 0;
}