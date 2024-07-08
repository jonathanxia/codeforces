// Link: https://codeforces.com/contest/1983/problem/D
#include <lib/constants/mod998244353.h>
#include <lib/vv/sum.h>
#include <lib/vv/counter.h>
#include <lib/vv/sort.h>
#include <lib/algo/inversion.h>
using namespace vv;

void solve() {
    ll n; cin >> n;
    vl a(n); cin >> a;
    vl b(n); cin >> b;
    ll na = algo::count_inversions(a);    
    ll nb = algo::count_inversions(b);

    if (mod(na, 2) != mod(nb, 2)) {
        print("NO"); return;
    }
    sort(a); sort(b);
    if (a != b) {
        print("NO"); return;
    }
    print("YES");
}

int main() {
    init();
    int t; cin >> t;
    cep(t) solve();
    return 0;
}