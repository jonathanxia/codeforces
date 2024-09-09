// Link: https://atcoder.jp/contests/abc370/tasks/abc370_f
#include <lib/constants/mod998244353.h>
#include <lib/vv/sum.h>
#include <lib/vv/counter.h>
#include <lib/vv/sort.h>
#include <lib/bitster.h>
#include <lib/cum.h>
#include <lib/datastruct/binary_lifting.h>
using namespace vv;

using V = ll;
V op(V a, V b) {
    return a + b;
}
V e() { return 0; }

void solve() {
    ll n, k; cin >> n >> k;
    vl a(n); cin >> a;
    ll total_cake = sum(a);
    FOR(i, 0, n - 1) a.push_back(a[i]);
    cum::sum<ll> cs(a);

    using BL = BinaryLift<V, op, e, 20>;
    auto fmod = [&](ll x) { return x >= n ? x - n : x; };
    auto create_jump_table = [&](ll cutoff) {
        // Fill out the first row first
        ll right = 0;
        vl nxt(n);
        vl dist(n);
        FOR(left, 0, n - 1) {
            while (cs.query(left, right) < cutoff) right++;
            nxt[left] = fmod(right + 1);
            dist[left] = right - left + 1;
        }
        return BL(nxt, dist);
    };

    // Now to check if something works
    auto works = [&](ll cutoff) {
        auto bl = create_jump_table(cutoff);
        // we need to check if the distance travelled is OK
        FOR(start, 0, n - 1) {
            ll d = bl.query_agg(start, k, false);
            if (d <= n) return true;
        }
        return false;
    };

    ll ans = largest_st(c, works(c), 0, total_cake);
    auto bl = create_jump_table(ans);
    ll ans1 = 0;
    FOR(i, 0, n - 1) if (bl.query_agg(i, k, false) > n) ans1++;
    print(ans, ans1);

}

int main() {
    init();
    solve();
    return 0;
}