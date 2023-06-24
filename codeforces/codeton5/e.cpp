#include <lib/common.h>

void solve() {
    ll n, k, A; cin >> n >> k >> A;
    vl x(n), y(n), c(n);
    rep(i, 0, n - 1) {
        cin >> x[i] >> y[i] >> c[i];
    }

    // Sort by y
    vl yidx = vv::argsort(y);
    x = vv::slice(x, yidx);
    y = vv::slice(y, yidx);
    c = vv::slice(c, yidx);
}

int main() {
    init();
    solve();
    return 0;
}