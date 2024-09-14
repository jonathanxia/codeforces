// Link: https://atcoder.jp/contests/abc366/tasks/abc366_g
#include <lib/constants/mod998244353.h>
#include <lib/vv/sum.h>
#include <lib/vv/counter.h>
#include <lib/vv/sort.h>
#include <lib/linalg/solve_linear.h>
#include <lib/mod_int.h>
using namespace vv;

void solve() {
    ll n, m; cin >> n >> m;
    matrix<ModInt<2>> mat(n, n);
    cepeat(m) {
        ll u, v; cin >> u >> v; u--; v--;
        mat(u, v) = 1;
        mat(v, u) = 1;
    }
    vector<ModInt<2>> b(n);
    auto res = linalg::solve_linear(mat, b);
    if (len(res) == 0) SAY_No;

    vl output(n);
    FOR(i, 1, len(res) - 1) {
        const vector<ModInt<2>>& soln = res[i];
        FOR(node, 0, n - 1) {
            nt::set_bit(output[node], i - 1, ll(soln[node]));
        }
    }
    if (all_st(x, output[x] > 0, 0, len(output) - 1)) {
        print("Yes");
        print(output);
    }
    else {
        print("No");
    }
}

int main() {
    init();
    solve();
    return 0;
}