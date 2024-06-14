#pragma once
#include <lib/common.h>

/**
 * BitTrie, a trie for numbers in binary.
 * 
 * Usage: https://codeforces.com/contest/1980/submission/265815427
 * 
 * BitTrie bt;
 * bt.add(5, 1); // Adds it one time
 * bt.add(5, -1); // Removes it
 * bt.count(5); // How many times 5 shows up
 */
template<class T, int num_bits>
struct BitTrie {
    struct node {
        array<int, 2> to;
        int cnt;

        node() {
            to = {-1, -1};
            cnt = 0;
        }

        friend ostream& operator<<(ostream& os, const node& bt) {
            os << "{" << "to: " << bt.to << " cnt: " << bt.cnt;
            return os;
        }
    };

    vector<node> trie;

    void clear() { trie = {node()}; }

    BitTrie() { clear(); }

    void add(T x, int cnt) {
        int u = 0;
        trie[0].cnt += cnt;
        for(int i = num_bits - 1; i >= 0; i--) {
            int bit = (x >> i) & 1;
            if(trie[u].to[bit] == -1) {
                trie[u].to[bit] = (int)trie.size();
                trie.push_back(node());
            }
            u = trie[u].to[bit];
            trie[u].cnt += cnt;
        }
    }

    // Returns how many times x the first `prefix_len` bits
    // of x show up. The last few bits of x are ignored.
    int count(T x, int prefix_len) const {
        assert(prefix_len <= num_bits);
        assert(prefix_len >= 0);
        int u = 0;
        for (int i = num_bits - 1; i >= num_bits - prefix_len; i--) {
            int bit = (x >> i) & 1;
            if (trie[u].to[bit] == -1) return 0;
            u = trie[u].to[bit];
        }
        return trie[u].cnt;
    }

    int count(T x) const {
        return count(x, num_bits);
    }

    // Returns the elements of the trie with their counts
    // Ignores zero count elements
    // Mostly for debugging
    vector<pair<T, int>> elements() const {
        T res(0);
        // Run a dfs
        vector<pair<T, int>> output;

        function<void(int, int)> dfs = [&](int u, int depth) {
            if (depth == 0 && trie[u].cnt > 0) output.push_back({res, trie[u].cnt});
            FOR(idx, 0, 1) {
                int v = trie[u].to[idx];
                if (v >= 0) {
                    res ^= T(idx) << (depth - 1);
                    dfs(v, depth - 1);
                    res ^= T(idx) << (depth - 1);
                }
            }
        };
        dfs(0, num_bits);
        return output;
    }

    // Computes the maximum (elem ^ x) for each elem in trie.
    // If the Trie is empty, returns 0.
    T max_xor(T x) {
        // First check the size.
        // Technically this is undefined, but given that we are looking for
        // max xor, it is safe to just return 0.
        if (trie[0].cnt <= 0) {
            return T(0);
        }
        int u = 0;
        T res = 0;
        for(int i = num_bits - 1; i >= 0; i--) {
            int bit = (x >> i) & 1;
            if(trie[u].to[bit ^ 1] != -1 && trie[trie[u].to[bit ^ 1]].cnt > 0) {
                res |= T(1) << i;
                u = trie[u].to[bit ^ 1];
            } else {
                u = trie[u].to[bit];
            }
        }

        return res;
    }
};

