// Link: https://codeforces.com/contest/2269/problem/D
#include <lib/constants/mod998244353.h>
#include <lib/vv/sum.h>
#include <lib/vv/counter.h>
#include <lib/vv/sort.h>
#include <lib/bitster.h>
#include <lib/datastruct/vec_and_sum.h>
using namespace vv;

void solve() {
    ll n, q; cin >> n >> q;    
    vl a(n); cin >> a;
    VectorAndSum<ll> is_even(LC(ll((__builtin_popcountl(x) & 1LL)==0), x, a));
    vl ans;
    ans.push_back(is_even.sum());
    cepeat(q) {
        ll p, x; cin >> p >> x;
        p--;
        a[p] = x;
        ll new_val = (__builtin_popcountl(x) & 1LL) == 0;
        is_even.assign(p, new_val);
        ans.push_back(is_even.sum());
    }
    print(ans);
}

int main() {
    init();
    int t; cin >> t;
    cep(t) solve();
    return 0;
}