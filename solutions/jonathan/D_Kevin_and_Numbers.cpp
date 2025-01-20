// Link: https://codeforces.com/contest/2061/problem/D
#include<lib/macros.h>
#include<lib/print.h>
#include<lib/inp.h>
#include<lib/common.h>
#include<lib/vv/sum.h>
#include<lib/vv/sort.h>
#include<lib/mset.h>

using namespace vv;

void solve() {
    ll n, m; cin >> n >> m;
    vl a(n); cin >> a; vl b(m); cin >> b;
    sort(a);
    sort(b);

    // Sum must be conservered
    if (sum(a) != sum(b)) {
        print("No"); return;
    }
    multiset<ll> aset(ALL(a));
    multiset<ll> bset(ALL(b));

    while (len(bset) <= len(aset)) {
        // dprint("bset now", bset, "aset=", aset);
        if (len(bset) == 0) {
            if (len(aset) == 0) {
                print("Yes"); return;
            }
            else {
                print("No"); return;
            }
        }
        ll mx = mset::popmax(bset);
        if (aset.count(mx)) {
            mset::erase(aset, mx);
            continue;
        }
        ll hlf = mx / 2;
        ll ulf = mx - hlf;
        bset.insert(hlf);
        bset.insert(ulf);
    }
    print("No");
}

int main() {
    init();
    int t; cin >> t;
    cep(t) solve();
    return 0;
}