#pragma once
#include <lib/tree/dfs_tree.h>

// Given a tree, answer queries of the form
//    get_ancestor(k, v) --> k-th parent of v
struct AncestorTree {
    vvi ancestors; // ancestors[i][v] gives the 2^i-th ancestor of v
    const ll log_depth = 24; // length of ancestors

    AncestorTree(const DfsTree& tree) {
        ll n = tree.n;
        ancestors = vvi(log_depth, vi(n));
        FOR(i, 0, n - 1) {
            // Induces a self-loop for the parent
            ancestors[0][i] = (i == tree.root) ? i : tree.parent[i];
        }

        FOR(i, 1, log_depth - 1) {
            FOR(vert, 0, n - 1) {
                ll kp = ancestors[i - 1][vert];
                ancestors[i][vert] = ancestors[i - 1][kp];
            }
        }
    }

    // Get the k-th ancestor of vertex v
    ll get_ancestor(ll k, ll v) const {
        ll ret = v;
        FOR(i, 0, log_depth - 1) {
            if ((1LL << i) > k) break;
            if ((1LL << i) & k) {
                ret = ancestors[i][ret];
            }
        }
        return ret;
    }
};
