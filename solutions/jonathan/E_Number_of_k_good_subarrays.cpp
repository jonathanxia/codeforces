// Link: https://codeforces.com/contest/1982/problem/E
#include<lib/mod_int.h>
#include<lib/nt.h>
#include<lib/macros.h>
#include<lib/vv.h>
#include<lib/print.h>
#include<lib/common.h>
#include<lib/inp.h>
// #include<lib/dp/digit_dp.h>

using namespace vv;
umap<array3, MI> cache;

void solve() {
    ll n; ll k; cin >> n >> k;
    n--;
    vi s = nt::get_digits(n, 2);
    FOR(i, 0, k + 1) s.push_back(0);
    reverse(ALL(s));

    // Global state for the upper bound to the dp. This must be reset every
    // time if the upper bound changes.
    //
    // Tip: Do not call func() directly, rather call rfunc which takes care of
    // reinitialization

    umap<array3, MI> dp;
    function<MI(ll, ll, ll)> func = [&](ll d, ll needed, ll under) {
        // Check for precomputation ----------------------------
        array3 params {d, needed, under};
        if (under && cache.count(params)) return cache[params];
        if (dp.count(params)) return dp[params];

        // Handle base cases here -------------------------------
        ll num_ones = k - needed;
        if (d < 0) return MI(0);
        if (num_ones > k) return MI(0);
        dprint("Calling func", d, needed, under);

        // I have three things
        //       x x x
        // 0 0 0 1 1 0
        if (needed > d - 2) {
            dprint("needed > d - 2", needed, d);
            if (under) cache[params] = 0;
            return dp[params] = 0;
        }
        MI ans = 0;
        if (needed == d - 2) {
            ll last = (1LL << (d - 1)) - 2;
            dprint("Needed", needed, "d=", d, "last=", last);
            if (!under) {
                chkmin(last, n % (1LL << d));
            }
            ans += MI(last + 1) * (MI(last) + 2) / 2;
            // dprint("ans=", ans);
        }

        if (under) {
            // We can pick any digit we want, though note that we
            // have not necessarily started yet
            FOR(i, 0, 1) {
                // Transition logic here ---------------------------
                ans += func(d - 1, needed - i, 1LL);
            }
            if (under) cache[params] = ans;
            return dp[params] = ans;
        }
        else {
            // Can only go up to the digit of the number
            ll digit = s[len(s) - d];
            FOR(i, 0, digit) {
                // Transition logic here ---------------------------
                ans += func(d - 1, needed - i, i < digit);
            }
            if (under) cache[params] = ans;
            return dp[params] = ans;
        }
    };

    // Answer extraction, problem dependent ---------------------
    print(func(len(s), k, 0));
    dbg(dp);
    dbg(cache);
    // dprint("dp size for", k, "->", len(dp));
}


int main() {
    init();
    int t; cin >> t;
    cep(t) solve();
    return 0;
}