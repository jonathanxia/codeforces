// Link: https://codeforces.com/contest/2269/problem/E
#include <lib/constants/mod998244353.h>
#include <lib/vv/init.h>
#include <lib/datastruct/cartesian_tree.h>
#include <lib/bitster.h>
#include <lib/ndarray.h>

vl cnt(1LL << 18);

void solve() {
    ll n; cin >> n; vl a(n); cin >> a;    
    MaxCartesianTree<ll> tree(a);

    ll K = 0;
    DOR(bp, 17, 0) {

        // Try setting the K bit and seeing if this is possible.
        K ^= 1LL << bp;

        vl a_mod(n); FOR(i, 0, n - 1) a_mod[i] = a[i] & K;
        ndarray<ll, 1> prefix_xor({n});
        FOR(i, 0, n - 1) prefix_xor(i) = prefix_xor(i - 1) ^ (a_mod[i]);

        function<ll(ll)> true_size = [&](ll node) {
            return node >= 0 ? tree.size(node) : -1;
        };

        function<void(ll)> clear_node = [&](ll node) {
            if (node < 0) return;
            FOR(i, tree.range_left[node], tree.range_right[node]) cnt[prefix_xor(i)] = 0;
        };

        function<bool(ll)> dfs = [&](ll m) {
            if (m == -1) return false;
            ll left_sz = true_size(tree.left_child[m]);
            ll right_sz = true_size(tree.right_child[m]);
            bool left_res, right_res;
            bool right_first = true;
            if (left_sz > right_sz) {
                // do right side first then left
                right_res = dfs(tree.right_child[m]);
                // Clear out the xor counts
                clear_node(tree.right_child[m]);
                left_res = dfs(tree.left_child[m]);
            }
            else {
                left_res = dfs(tree.left_child[m]);
                clear_node(tree.left_child[m]);
                right_res = dfs(tree.right_child[m]);
                right_first = false;
            }
            if (left_res || right_res) return true;

            ll L, R;
            if (right_first) {
                L = m; R = tree.range_right[m];
                cnt[prefix_xor(tree.range_left[m] - 1)]++;
            }
            else {
                L = tree.range_left[m] - 1; R = m - 1;
                cnt[prefix_xor(m)]++;
            }
            ll found = 0;
            FOR(i, L, R) {
                ll need = K ^ prefix_xor(i);
                found += cnt[need];
            }
            // now check if there is a forbidden (m - 1, m)
            if ((prefix_xor(m - 1) ^ prefix_xor(m)) == K) found--;

            // undo the modifications
            if (right_first)  cnt[prefix_xor(tree.range_left[m] - 1)]--;
            else cnt[prefix_xor(m)]--;

            // Fulfill our contract and add everything in
            if (right_first) { L = m; R = tree.range_right[m]; }
            else { L = tree.range_left[m]; R = m; }
            FOR(i, L, R) cnt[prefix_xor(i)]++;

            return (found > 0) && ((a_mod[m] & K) == K);
        };

        bool res = dfs(tree.root);
        if (! res) {
            // Disable the bit in K and move on
            K ^= (1LL << bp);
        }
        FOR(i, 0, n - 1) cnt[prefix_xor(i)] = 0;
    }

    print(K);
    // Reset the cnts
}

int main() {
    init();
    int t; cin >> t;
    cep(t) solve();
    return 0;
}