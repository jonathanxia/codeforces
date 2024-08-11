// Link: https://codeforces.com/contest/1998/problem/E2
#include <lib/vv/sum.h>
#include <lib/vv/counter.h>
#include <lib/vv/sort.h>
#include <lib/sparsetable.h>
#include <lib/cum.h>
using namespace vv;

void solve() {
    ll n, x; cin >> n >> x;
    vl a(n); cin >> a;
    MaxSparseTable<ll> st(a);
    cum::sum<ll> cs(a);

    ll ans = 0;
    FOR(i, 0, n - 1) {
        // Can i achieve world domination?
        bool dominated = false;
        ll left = i;
        ll right = i;
        while (true) {
            ll s = cs.query(left, right);
            ll new_left;
            if (left > 0)
                new_left = smallest_st(li, st.query(li, left - 1) <= s, 0, left - 1);
            else new_left = 0;

            ll new_right;
            if (right < n - 1) new_right = largest_st(ri, st.query(right + 1, ri) <= s, right + 1, n - 1);
            else new_right = n - 1;

            if (new_left == 0 && new_right == n - 1) {
                dominated = true;
                break;
            }
            if (new_left == left && new_right == right) {
                dominated = false;
                break;
            }
            left = new_left;
            right = new_right;
        }
        if (dominated) ans++;
    }
    print(ans);
}

int main() {
    init();
    int t; cin >> t;
    cep(t) solve();
    return 0;
}