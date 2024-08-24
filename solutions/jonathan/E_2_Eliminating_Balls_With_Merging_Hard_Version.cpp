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
 
    auto findleft = [&](ll left, ll right) {
        ll s = cs.query(left, right);
        ll l = left;
        while (l > 0) {
            l = smallest_st(j, st.query(j, l - 1) <= s, 0, l - 1);
            if (s == cs.query(l, right)) return l;
            s = cs.query(l, right);
        }
        return l;
    };
 
    vl output;
    map<ll, ll> intervals;
    FOR(r, 0, n - 1) {
        vl to_delete;
        map<ll, ll> new_intervals;
        foreachp(l, v, intervals) {
            if (cs.query(l, r - 1) < a[r]) to_delete.pb(l);
        }
        foreach(d, to_delete) intervals.erase(d);
        intervals[r]++;
        foreachp(l, v, intervals) {
            new_intervals[findleft(l, r)] += v;
        }
        intervals = new_intervals;
        output.pb(intervals[0]);
    }
    print(output);
}

int main() {
    init();
    int t; cin >> t;
    cep(t) solve();
    return 0;
}