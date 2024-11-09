// Link: https://codeforces.com/contest/2029/problem/E
#include<lib/constants/mod998244353.h>
#include<lib/common.h>
#include<lib/vv/sum.h>
#include<lib/vv/counter.h>
#include<lib/vv/sort.h>
#include<lib/vv/gcd.h>
#include<lib/vv/all.h>
#include<lib/nt.h>
#include <lib/nt/smallest_prime_div.h>
using namespace vv;

nt::SmallestPrimeDiv spd;

void solve() {
    ll n; cin >> n;
    vl a(n); cin >> a;
    // dbg(vl(SLC(smallest_prime_div, 0, 10)));
    ll g = vv::gcd(a);
    if (g > 1) {
        print(g); return;
    }
    vb composite_flag = LC(!nt::is_prime(x), x, a);
    if (vv::all(composite_flag)) {
        print(2); return;
    }
    // There exists some prime number and some thing not divisible by that prime number
    ll num_primes = 0;
    ll p = -1;
    foreach(x, a) if (nt::is_prime(x)) {
        p = x;
        num_primes++;
    }
    if (num_primes > 1) {
        print(-1); return;
    }
    sort(a);
    if (a[0] != p || a[1] < 2 * p) {
        print(-1); return;
    }
    FOR(i, 1, n - 1) {
        ll k = spd.query(a[i]);
        ll rem = a[i] / k;
        if (a[i] % p == 0) continue;

        if (a[i] % 2 == 1 && (a[i] - k) / 2 >= p) continue;
        if (a[i] % 2 == 0 && a[i] / 2 >= p) continue;
        print(-1); return;
    }
    print(p);
}

int main() {
    init();
    nt::do_sieve(410'000);
    int t; cin >> t;
    cep(t) solve();
    return 0;
}