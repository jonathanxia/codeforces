#define PROBLEM "https://atcoder.jp/contests/abc356/tasks/abc356_d"

#include <lib/vv.h>

using namespace vv;

void solve() {
    ll n, m; cin >> n >> m;

    MI ans = 0;
    FOR(pos, 0, 60) {
        if (nt::get_bit(m, pos)) {
            ans += bitster::num_with_bit_set(n, pos);
        }
    }
    print(ans);
}

int main() {
    init();
    solve();
    return 0;
}