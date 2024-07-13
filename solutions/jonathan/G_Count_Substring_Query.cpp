// Link: https://atcoder.jp/contests/abc362/tasks/abc362_g
#include <lib/string/suffix_automaton.h>

void solve() {
    string s; cin >> s;
    ll q; cin >> q;
    SuffixAutomaton sa(s);
    cepeat(q) {
        string t; cin >> t;
        print(sa.num_occurrences(t));
    }
}

int main() {
    init();
    solve();
    return 0;
}