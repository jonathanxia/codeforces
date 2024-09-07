// Link: https://codeforces.com/contest/1982/problem/F
#include<lib/common.h>
#include<lib/mset.h>
#include <lib/datastruct/acsegtree/seg_max.h>
#include <lib/datastruct/acsegtree/seg_min.h>

void solve() {
    ll n; cin >> n; vl a(n); cin >> a;
    ll q; cin >> q;
    set<ll> bad_indices; // i means (i, i + 1) out of order
    FOR(i, 0, n - 2) {
        if (a[i] > a[i + 1]) bad_indices.insert(i);
    }
    seg_min::SegTree seg(a);
    seg_max::SegTree seg2(a);
    auto run_query = [&]() {
        if (len(bad_indices) == 0) {
            print(-1, -1); return;
        }
        ll idx = mset::min(bad_indices);
        ll mn = seg.query(idx + 1, n - 1);
        ll left = largest_st(i, a[i] <= mn, 0, idx);
        left++;

        idx = mset::max(bad_indices) + 1;
        ll mx = seg2.query(0, idx - 1);
        ll right = smallest_st(i, a[i] >= mx, idx, n - 1);
        right--;
        print(1 + left, 1 + right);
    };

    run_query();
    cepeat(q) {
        ll idx, x; cin >> idx >> x;
        idx--;
        a[idx] = x;
        bad_indices.erase(idx - 1);
        bad_indices.erase(idx);
        if (ordered(0, idx + 1, n - 1) && a[idx] > a[idx + 1]) bad_indices.insert(idx);
        if (ordered(0, idx - 1, n - 1) && a[idx - 1] > a[idx]) bad_indices.insert(idx - 1);
        seg.update(idx, x);
        seg2.update(idx, x);
        run_query();
    }
}

int main() {
    init();
    int t; cin >> t;
    cep(t) solve();
    return 0;
}