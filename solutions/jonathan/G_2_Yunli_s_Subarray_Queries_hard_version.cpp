// Link: https://codeforces.com/contest/2009/problem/G2
#include <lib/vv/sort.h>
#include <lib/mset.h>
#include <lib/sparsetable.h>
#include <lib/datastruct/acsegtree/lazy_assign_sum.h>

using namespace vv;

void solve() {
    ll n, k, q; cin >> n >> k >> q;
    vl a(n); cin >> a;
    // Transform array
    FOR(i, 0, n - 1) a[i] = a[i] - i;

    vl needs(n - k + 1, 1e18);
    {
        umapll counts;
        set<pl> freqs;
        auto insert_elem = [&](ll x) {
            ll c = counts[x];
            counts.erase(x);
            counts[x] = c + 1;
            freqs.erase({c, x});
            freqs.insert({c + 1, x});
        };
        auto delete_elem = [&](ll x) {
            ll c = counts[x];
            counts[x] = c - 1;
            freqs.erase({c, x});
            freqs.insert({c - 1, x});
        };
        FOR(i, 0, k - 1) {
            insert_elem(a[i]);
        }
        needs[0] = k - mset::max(freqs).first;

        FOR(i, 1, n - k) {
            // i through i + k - 1 inclusive
            delete_elem(a[i - 1]);
            insert_elem(a[i + k - 1]);
            needs[i] = k - mset::max(freqs).first;
        }
    }

    // needs[i] = i->i+k-1
    vector<array3> queries;
    FOR(qi, 0, q - 1) {
        ll l, r; cin >> l >> r;
        l--; r--;
        r -= (k - 1);
        queries.push_back({l, r, qi});
    }
    MinSparseTable<ll> st(needs);
    rsort(queries);
    ll left = n - k;

    // Set up the first base case
    lazy_assign_sum::LazySegTree seg(n - k + 1);
    seg.update(left, left, {needs[left], 1LL});

    vl output(q);
    foreach(query, queries) {
        while (left > query[0]) {
            // Shift the data structure left a bit
            left--;
            ll right = largest_st(j, st.query(left, j) >= needs[left], left, n - k);
            seg.update(left, right, {needs[left], 1LL});
        }

        output[query[2]] = seg.query(query[0], query[1]).sm;
    }
    foreach(o, output) print(o);
}

int main() {
    init();
    int t; cin >> t;
    cep(t) solve();
    return 0;
}
