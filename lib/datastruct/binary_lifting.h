#pragma once

#include <lib/common.h>

/**
 * A generic binary lifting datastructure. The representation is that we have
 * n nodes. Each of these nodes has a next[node] which points to some other node.
 * 
 * Each node also have a value, denoted value[node]. We then supply a merge function
 * that determines how these values should be merged together
 * 
 * We also have MX_LEVEL which determines how many times to binary lift.
*/
template <typename V, V(*op)(V, V), V(*e)(), int MX_LEVEL=31>
struct BinaryLift {
    vvi jump_node; // jump_node[level][node] = which node after 2^level hops
    vector<vector<V>> agg_value; // agg_value[level][node] = aggregated values

    template <typename S>
    BinaryLift(const vector<S>& nxt, const vector<V>& values) : jump_node(MX_LEVEL, vi(len(nxt))),
        agg_value(MX_LEVEL, vector<V>(len(nxt)))
    {
        ll n = len(nxt);
        FOR(i, 0, n - 1) jump_node[0][i] = nxt[i];
        FOR(i, 0, n - 1) agg_value[0][i] = values[i];

        // Proceed to binary lift
        FOR(j, 1, MX_LEVEL - 1) {
            FOR(node, 0, n - 1) {
                ll mid_node = jump_node[j - 1][node];
                ll new_node = jump_node[j - 1][mid_node];
                jump_node[j][node] = new_node;
                agg_value[j][node] = op(agg_value[j - 1][node], agg_value[j - 1][mid_node]);
            }
        }
    }

    // Returns where you would be after k hops, denoted node+k
    ll query_node(ll node, ll k) {
        FOR(idx, 0, MX_LEVEL - 1) {
            if (k == 0) return node;
            if (k & (1LL << idx)) {
                k ^= (1LL << idx);
                node = jump_node[idx][node];
            }
        }
        return node;
    }

    /**
     * Query the op(node, node+1, node+2, ..., node+k)
     * 
     * inclusive flag as to whether or not to include node+k or not
    */
    V query_agg(ll node, ll k, bool inclusive=true) {
        V ans = e();
        FOR(idx, 0, MX_LEVEL - 1) {
            if (k == 0) break;
            if (k & (1LL << idx)) {
                k ^= (1LL << idx);
                ans = op(ans, agg_value[idx][node]);
                node = jump_node[idx][node];
            }
        }
        if (inclusive) {
            // Just slap on the last value
            ans = op(ans, agg_value[0][node]);
        }
        return ans;
    }
};

// using V = ll;
// V op(V a, V b) {
//     return a + b;
// }
// V e() { return 0; }

