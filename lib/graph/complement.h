#pragma once
#include <lib/common.h>

namespace graph {
    /**
     * Computes the complement of a graph.
     * 
     * Runtime: O(n^2) where n is number of vertices
     */
    vvpl complement(const vvpl& g) {
        vvpl ret(g.size());
        ll n = g.size();
        vvb adj_matrix(n, vb(n));
        FOR(v, 0, n - 1) foreachp(u, w, g[v]) {
            adj_matrix[v][u] = true;
        }
        FOR(v, 0, n - 1) FOR(u, 0, n - 1) {
            if (u == v) continue;
            if (!adj_matrix[v][u]) ret[v].pb({u, 1});
        }
        return ret;
    }
}