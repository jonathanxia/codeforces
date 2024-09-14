// Link: https://codeforces.com/contest/2005/problem/D
#include <lib/vv/sort.h>
#include <lib/sparsetable.h>
#include <lib/vv/unique.h>
using namespace vv;

void solve() {
    ll n; cin >> n; vl a(n); cin >> a; vl b(n); cin >> b;
    GcdSparseTable<ll> ast(a);
    GcdSparseTable<ll> bst(b);

    map<ll, ll> counts;

    vl a_sfx_indices = {0};
    vl b_sfx_indices = {0};
    FOR(i, 1, n - 1) {
        if (ast.query(i, n - 1) != ast.query(a_sfx_indices.back(), n - 1)) {
            a_sfx_indices.push_back(i);
        }
        if (bst.query(i, n - 1) != bst.query(b_sfx_indices.back(), n - 1)) {
            b_sfx_indices.push_back(i);
        }
    }
    a_sfx_indices.push_back(n);
    b_sfx_indices.push_back(n);
    // dbg(a_sfx_indices);
    // dbg(b_sfx_indices);

    // First assume that the first element is fixed
    FOR(i, 1, n - 1) {
        ll g1 = ast.query(0, i - 1);
        ll g2 = bst.query(0, i - 1);

        // Starting from i, determine all change points for a and b
        vl a_fwd_changes = {i};
        vl b_fwd_changes = {i};
        ll j = i;
        while (j < n) {
            j = smallest_st(k, ast.query(i, k) != ast.query(i, a_fwd_changes.back()), j, n - 1);
            if (j < n) a_fwd_changes.push_back(j);
        }
        j = i;
        while (j < n) {
            j = smallest_st(k, bst.query(i, k) != bst.query(i, b_fwd_changes.back()), j, n - 1);
            if (j < n) b_fwd_changes.push_back(j);
        }

        // Alright let's figure out the answer now
        foreach(idx, a_sfx_indices) if (idx-1 >= i) a_fwd_changes.push_back(idx - 1);
        foreach(idx, b_sfx_indices) if (idx - 1 >= i) a_fwd_changes.push_back(idx - 1);
        foreach(idx, b_fwd_changes) a_fwd_changes.push_back(idx);
        a_fwd_changes.push_back(n);
        a_fwd_changes = unique(a_fwd_changes);
        sort(a_fwd_changes);
        // dprint(i, "fwd changes ->", a_fwd_changes);
        FOR(ii2, 0, len(a_fwd_changes) - 2) {
            ll i2 = a_fwd_changes[ii2];
            ll i3 = a_fwd_changes[ii2 + 1];
            ll value1 = gcd(gcd(g1, bst.query(i, i2)), ast.query(i2 + 1, n - 1));
            ll value2 = gcd(gcd(g2, ast.query(i, i2)), bst.query(i2 + 1, n - 1));
            // dprint("   ", i2, "->", i3, ":", value1, "+", value2);
            counts[value1 + value2] += i3 - i2;
        }
    }
    FOR(i, 0, n - 1) {
        // Flip 0 through i
        ll value1 = gcd(ast.query(0, i), bst.query(i + 1, n - 1));
        ll value2 = gcd(bst.query(0, i), ast.query(i + 1, n - 1));
        counts[value1 + value2]++;
    }
    pl ans = {-1, -1};
    foreach(p, counts) {
        chkmax(ans, p);
    }
    print(ans.first, ans.second);
}

int main() {
    init();
    int t; cin >> t;
    cep(t) solve();
    return 0;
}