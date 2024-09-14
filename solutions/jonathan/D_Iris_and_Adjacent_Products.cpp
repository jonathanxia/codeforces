// Link: https://codeforces.com/contest/2006/problem/D
#include <lib/vv/sort.h>
#include <lib/algo/mos_algo.h>
using namespace vv;

ll calc_ans(const vl& lows, const vl& highs) {
    ll m = len(highs);
    ll ans = 0;
    ll num_spots = 1;
    FOR(i, 0, m - 1) {
        // Simple case
        if (highs[i] == 0 && lows[i] == 0) {
            num_spots += lows[i]; continue;
        }

        if (num_spots == 0) {
            num_spots += 2;
            ans++;
        }
        num_spots += lows[i];
        if (highs[i] <= num_spots) {
            num_spots -= highs[i];
            continue;
        }
        ll remaining = highs[i] - num_spots;
        num_spots = 0;
        ll p = ceildiv(remaining, 2);
        ans += p;
        num_spots += 2 * p - remaining;
    }
    return ans;
}

void solve() {
    ll n, q, k; cin >> n >> q >> k;    
    vl b(n); cin >> b;

    ll SQRT_MX = ll(sqrt(k)) + 3;
    vl lows(SQRT_MX);
    vl highs(SQRT_MX);
    vector<Query> queries(q);
    vl output(q);
    FOR(idx, 0, q - 1) {
        ll l, r; cin >> l >> r; l--; r--;
        queries[idx] = Query(l, r, idx);
    }
    sort(queries);
    ll left = 0;
    ll right = -1;
    auto func = [&](ll val, ll delta) {
        if (val * val <= k) {
            lows[val] += delta;
        }
        else {
            val = k / val;
            highs[val] += delta;
        }
    };
    foreach(query, queries) {
        // Do expansions first
        while (right < query.right) {
            right++;
            func(b[right], 1);
        }
        while (left > query.left) {
            left--;
            func(b[left], 1);
        }
        // Then contractions
        while (right > query.right) {
            func(b[right], -1);
            right--;
        }
        while (left < query.left) {
            func(b[left], -1);
            left++;
        }

        // Query the datastructure
        ll ans = calc_ans(lows, highs);
        output[query.idx] = ans;
    }
    print(output);
}

int main() {
    init();
    int t; cin >> t;
    cep(t) solve();
    return 0;
}