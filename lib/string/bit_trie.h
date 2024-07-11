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
namespace str {
    struct bit_trie_default_node {
        array<int, 2> to;
        int cnt;

        bit_trie_default_node() {
            to = {-1, -1};
            cnt = 0;
        }

        friend ostream& operator<<(ostream& os, const bit_trie_default_node& bt) {
            os << "{" << "to: " << bt.to << " cnt: " << bt.cnt;
            return os;
        }
    };

    template<typename T, int num_bits, typename node=str::bit_trie_default_node>
    struct BitTrie {
        vector<node> trie;

        void clear() { trie = {node()}; }

        BitTrie() { clear(); }

        // Note that this is backwards from nt::get_bit
        static int get_bit(T x, int idx) {
            return (x >> (num_bits - idx - 1)) & 1;
        }
        static T MAX() {
            return (T(1) << num_bits) - 1;
        }

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

        void insert(T x) { add(x, 1); }
        void erase(T x) { add(x, -1); }

        // Returns a list of nodes traversed, starting from the root
        // Using each of these indices, you can get the nodes:
        // foreach(idx, bit_trie.traverse(x)) bit_trie.trie[idx]
        vector<int> traverse(T x) const {
            vector<int> output;
            int u = 0;
            DOR(i, num_bits - 1, 0) {
                output.push_back(u);
                int bit = (x >> i) & 1;
                if (trie[u].to[bit] == -1) return output;
                u = trie[u].to[bit];
            }
            output.push_back(u);
            return output;
        }

        // Returns the index in the trie for this element x
        // -1 if not present
        int find(T x, int prefix_len) const {
            assert(prefix_len <= num_bits);
            assert(prefix_len >= 0);
            vi indices = traverse(x);
            return prefix_len < len(indices) ? indices[prefix_len] : -1;
        }
        int find(T x) { return this->find(x, num_bits); }

        // Returns how many times x the first `prefix_len` bits
        // of x show up. The last few bits of x are ignored.
        int count(T x, int prefix_len) const {
            int u = find(x, prefix_len);
            if (u == -1) return 0;
            return this->trie[u].cnt;
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
} // namespace str
