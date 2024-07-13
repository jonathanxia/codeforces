// Link: https://codeforces.com/contest/128/problem/B
#include <lib/string/suffix_automaton.h>

void solve() {
    string s; cin >> s; ll k; cin >> k;
    SuffixAutomaton sa(s);
    if (sa.tot_count[0] - len(s) < k) {
        print("No such line."); return;
    }
    print(sa.kth_lexo_string(k));
}

int main() {
    init();
    solve();
    return 0;
}