// Link: https://codeforces.com/contest/1997/problem/E
#include <lib/vv/max.h>
#include <lib/datastruct/acsegtree/seg_sum.h>
#include <lib/mset.h>

using namespace vv;
void solve() {
    ll n, q; cin >> n >> q;
    vl a(n); cin >> a;
    umaplvl a_to_idx;
    FOR(i, 0, n - 1) a_to_idx[a[i]].pb(i);

    vector<string> output(q);
    map<ll, set<pl>> queries;
    FOR(i, 0, q - 1) {
        ll idx, x; cin >> idx >> x;
        idx--;
        queries[x].insert({idx, i});
    }

    vl monster_idx(n + 1); // Next monster to fight for each k
    seg_sum::SegTree seg(n); FOR(i, 0, n - 1) seg.set(i, 1);

    set<ll> active_ks; FOR(i, 1, n) active_ks.insert(i);
    FOR(level, 1, n) {
        vl to_delete;
        foreach(k, active_ks) {
            ll nxt = seg.largest_right_st(monster_idx[k], [&](ll x) { return x <= k; }) + 1;

            // From monster_idx[k] to nxt - 1 inclusive, the hero had `level`
            // All queries with this k and these indices should be answered
            while (queries[k].size() > 0 && mset::min(queries[k]).first < nxt) {
                auto [idx, q_idx] = mset::popmin(queries[k]);
                if (a[idx] < level) output[q_idx] = "NO";
                else output[q_idx] = "YES";
            }
            // dprint("Level=", level, "k=", k, "range is", monster_idx[k], "to", nxt - 1);
            monster_idx[k] = nxt;
            if (nxt == n) to_delete.pb(k);
        }
        foreach(k, to_delete) active_ks.erase(k);

        // Update segtree by removing all things with health level
        foreach(idx, a_to_idx[level]) seg.set(idx, 0);
    }
    foreach(s, output) print(s);
}

int main() {
    init();
    solve();
    return 0;
}