// Link: https://codeforces.com/contest/1993/problem/E
#include<lib/common.h>
#include<lib/bitster.h>
#include<lib/ndarray.h>
#include <lib/graph/tsp.h>

ndarray<ll, 2> func(ndarray<ll, 2>& a) {
    auto [n, m] = a.dimensions;

    // Now run this for one dimension and then the other
    ndarray<ll, 2> w({n, n});
    FOR(i, 0, n - 1) {
        FOR(j, 0, n - 1) {
            FOR(k, 0, m - 1) {
                w(i, j) += abs(a(i, k) - a(j, k));
            }
        }
    }
    return graph::tsp_with_dp(w);
}

void solve() {
    ll n, m; cin >> n >> m;
    ndarray<ll, 2> a({n + 1, m + 1});
    FOR(i, 0, n - 1) FOR(j, 0, m - 1) {
        cin >> a(i, j);
        a(n, j) ^= a(i, j);
        a(i, m) ^= a(i, j);
        a(n, m) ^= a(i, j);
    }
    ll ans = 1e18;
    vector<ndarray<ll, 2>> remove_row_dp;
    vector<ndarray<ll, 2>> remove_col_dp;
    FOR(i, 0, n) {
        // Suppose you remove row i
        ndarray<ll, 2> b({m + 1, n});
        FOR(row, 0, n) {
            if (row == i) continue;
            FOR(j, 0, m) b(j, row - (row > i)) = a(row, j);
        }
        remove_row_dp.push_back(func(b));
    }

    FOR(j, 0, m) {
        // Suppose you remove column j
        ndarray<ll, 2> b({n + 1, m});
        FOR(col, 0, m) {
            if (col == j) continue;
            FOR(i, 0, n) b(i, col - (col > j)) = a(i, col);
        }
        remove_col_dp.push_back(func(b));
    }

    // Try every combination
    FOR(i, 0, n) {
        FOR(j, 0, m) {
            ll row_ans = 1e18;
            ll mask = (1LL << (m + 1)) - 1;
            mask ^= (1LL << j);
            FOR(last, 0, m) if (last != j) {
                chkmin(row_ans, remove_row_dp[i](last, mask));
            }

            ll col_ans = 1e18;
            mask = (1LL << (n + 1)) - 1;
            mask ^= (1LL << i);
            FOR(last, 0, n) if (last != i) {
                chkmin(col_ans, remove_col_dp[j](last, mask));
            }
            chkmin(ans, col_ans + row_ans);
        }
    }
    print(ans);
}

int main() {
    init();
    int t; cin >> t;
    cep(t) solve();
    return 0;
}