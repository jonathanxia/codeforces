// Link: https://atcoder.jp/contests/abc364/tasks/abc364_c
#include<lib/vv/sort.h>
#include<lib/cum.h>
#include<lib/common.h>

using namespace vv;

void solve() {
    ll n, x, y; cin >> n >> x >> y;
    vl a(n); cin >> a;
    vl b(n); cin >> b;
    rsort(a);
    rsort(b);
    cum::sum<ll> ca(a);
    cum::sum<ll> cb(b);
    ll ans_a = first_st(i, ca[i] > x, 0, n - 1);
    ll ans_b = first_st(i, cb[i] > y, 0, n - 1);
    ll ans = min(ans_a, ans_b) + 1;
    print(ans == n + 1 ? n : ans);
}

int main() {
    init();
    solve();
    return 0;
}