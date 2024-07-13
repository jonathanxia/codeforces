// Link: https://atcoder.jp/contests/abc097/tasks/arc097_a
#include<lib/string/suffix_automaton.h>

void solve() {
    string s; cin >> s;
    ll k; cin >> k;

    SuffixAutomaton sa(s);
    print(sa.kth_unique_lexo_string(k));
}

int main() {
    init();
    solve();
    return 0;
}