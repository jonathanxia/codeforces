// Link: https://codeforces.com/contest/1983/problem/F
#include <lib/constants/mod998244353.h>
#include <lib/common.h>
#include <lib/string/bit_trie.h>

struct node {
    array<int, 2> to;
    int cnt;
    int max_idx;

    node() {
        to = {-1, -1};
        cnt = 0;
        max_idx = -1e9;
    }

    friend ostream& operator<<(ostream& os, const node& bt) {
        os << "{" << "to: " << bt.to << " cnt: " << bt.cnt << " " << bt.max_idx << "}";
        return os;
    }
};

void update_bit(str::BitTrie<ll, 30, node>& bt, ll x, int idx) {
    bt.insert(x);
    vi idxs = bt.traverse(x);
    foreach(u, idxs) {
        chkmax(bt.trie[u].max_idx, idx);
    }
}

void solve() {
    ll n, k; cin >> n >> k;
    vl a(n); cin >> a;
    auto func = [&](ll x) {
        str::BitTrie<ll, 30, node> bt;
        update_bit(bt, a[0], 0);
        ll ans = 0;
        ll mx_idx = -1; // Max index that works, where [mx_idx, hi] is good
        FOR(i, 1, n - 1) {
            // Answer, how many segments [j, i] are there
            // such that the answer is <= x
            // Can we find a[i] to match with somebody?
            int u = 0;
            FOR(ti, 0, 29) {
                ll b = bt.get_bit(a[i], ti);
                // Can we afford to have a 1 here?
                if (bt.get_bit(x, ti) == 1) {
                    // We either allow the 1 and continue the traversal
                    // or we continue down
                    ll c = bt.trie[u].to[b];
                    chkmax(mx_idx, c < 0 || bt.trie[c].cnt == 0 ? -1 : bt.trie[c].max_idx);

                    // Now if we allow 1 but require exact traversal
                    u = bt.trie[u].to[b ^ 1];
                }
                else {
                    // Require a 0 here, so we must match the bit
                    u = bt.trie[u].to[b];
                }
                if (u == -1) break;
            }
            if (u >= 0) chkmax(mx_idx, bt.trie[u].max_idx);
            ans += mx_idx + 1;

            update_bit(bt, a[i], i);
        }
        return ans;
    };

    ll MX = (1LL << 30) - 1;
    ll res = smallest_st(x, func(x) >= k, 0, MX);
    print(res);
}

int main() {
    init();
    int t; cin >> t;
    cep(t) solve();
    return 0;
}