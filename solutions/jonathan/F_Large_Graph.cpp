// Link: https://codeforces.com/contest/1978/problem/F
#include<lib/vv/sum.h>
#include<lib/common.h>
#include<lib/nt.h>
#include<lib/commit_dsu.h>

const ll MX = 1000 * 1000 + 1;
vvl prime_divisors(MX + 1);

void solve() {
    ll n, k; cin >> n >> k; vl a(n); cin >> a;
    ll n_ones = vv::sum(LC(ll(x == 1), x, a));

    vl b;
    FOR(i, 1, n - 1) b.push_back(a[i]);
    FOR(i, 0, n - 1) b.push_back(a[i]);
    a = b;
    ll n_new_ones = vv::sum(LC(ll(x == 1), x, a));

    DSU dsu(len(a));
    map<ll, vl> pset;
    FOR(i, 0, len(a) - 1) {
        foreach(p, prime_divisors[a[i]]) pset[p].push_back(i);
    }

    foreachp(p, v, pset) {
        // Do some uniting
        ll L = len(v);
        FOR(i, 0, L - 2) {
            ll idx1 = v[i];
            ll idx2 = v[i + 1];
            if (idx2 - idx1 <= k) {
                dsu.unite(idx1, idx2);
            }
        }
    }
    ll nc = dsu.num_components.value();
    print(nc - n_new_ones + n_ones * n);
}

int main() {
    init();
    nt::do_sieve(MX + 1);
    foreach(p, nt::primes) {
        SFOR(i, p, MX, p) {
            prime_divisors[i].push_back(p);
        }
    }
    int t; cin >> t;
    cep(t) solve();
    return 0;
}