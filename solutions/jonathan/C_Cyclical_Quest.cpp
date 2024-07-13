// Link: https://codeforces.com/contest/235/problem/C
#include <atcoder/string>
#include <lib/string/suffix_automaton.h>

void solve() {
    string s; cin >> s;
    ll q; cin >> q;

    SuffixAutomaton sa(s);

    cepeat(q) {
        string x; cin >> x;
        string y = x + x;
        vi z = atcoder::z_algorithm(y);
        ll stop = first_st(i, z[i] >= len(x), 1, len(y) - 1);
        ll ans = 0;
        ll m = len(x);

        // Look for substrings of y inside of s
        ll p = 0;
        ll L = 0;
        ll R = -1;
        while (true) {
            // True-up the interval that we are looking at so we have
            // accurate state
            while (p != 0 && sa.length[sa.link[p]] >= R - L + 1) {
                p = sa.link[p];
            }

            // Check to see if this is a valid config
            if (R - L + 1 == m && L < stop) {
                ans += sa.endpos_size[p];
            }
            // Move on to the next config, can we move to the
            // right?
            if (R < len(y) && R - L + 1 < m && sa.to[p].count(y[R + 1]) > 0) {
                // Move to the right by one
                p = sa.to[p][y[R + 1]];
                R++;
                continue;
            }
            // Can we move to the left by one?
            L++;
            if (L >= stop) break;
        }
        print(ans);
    }
}

int main() {
    init();
    solve();
    return 0;
}