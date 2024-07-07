// Link: https://codeforces.com/contest/1983/problem/E
#include <lib/constants/mod1000000007.h>
#include <lib/vv/sum.h>
#include <lib/vv/counter.h>
#include <lib/vv/sort.h>
#include <lib/mod_int.h>
using namespace vv;

void solve() {
    ll n; cin >> n; ll k; cin >> k;
    vMI v(n); cin >> v;

    MI alice = 0;
    ll j = n - k;
    if (j % 2 == 0) {
        alice += sum(v, k, n - 1) / 2;
        MI p = MI(j / 2 + 1) / (j + 1);
        alice += p * sum(v, 0, k - 1);
    }
    else {
        alice += sum(v, k, n - 1) * MI(j + 1) / (2 * j);
        MI p = MI((j + 1) / 2) / (j + 1);
        alice += p * sum(v, 0, k - 1);
    }
    print(alice, sum(v) - alice);
}

int main() {
    init();
    int t; cin >> t;
    cep(t) solve();
    return 0;
}