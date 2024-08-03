// Link: https://codeforces.com/contest/1995/problem/D
#include <lib/bitster/submask_set.h>
#include <lib/cum.h>

void solve() {
    ll n, c, k; cin >> n >> c >> k;
    string s; cin >> s;
    vvl indicators(c, vl(n));
    FOR(i, 0, n - 1) {
        indicators[s[i] - 'A'][i] = 1;
    }
    vector<cum::sum<ll>> cs;
    FOR(i, 0, c - 1) {
        cs.push_back(cum::sum<ll>(indicators[i]));
    }

    SubmaskSet submask_set(c);
    // So now that we have the cumsums, we can figure out what is bad
    FOR(i, 0, n - 1) {
        ll mask = (1LL << c) - 1;
        FOR(ch, 0, c - 1) {
            if (cs[ch].query(i, i + k - 1) > 0) {
                mask ^= (1LL << ch);
            }
        }
        submask_set.insert_submasks(mask);
    }
    ll ans = 1e18;
    FOR(mask, 0, (1LL << c) - 1) {
        if (submask_set.count(mask)) continue;
        chkmin(ans, __builtin_popcountl(mask));
    }
    print(ans);
}

int main() {
    init();
    int t; cin >> t;
    cep(t) solve();
    return 0;
}