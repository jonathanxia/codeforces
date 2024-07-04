#pragma once
#include <lib/common.h>

namespace graph {
    // Input: a matrix m with:
    // m[i][i] = 0 for all i
    // m[i][j] = weight(i, j) for adjecent nodes i, j
    // m[i][j] = graph::inf for non-adjacent nodes i, j
    void floyd_warshall(vvl& m)
    {
        const ll inf = 1LL << 62;
        int n = len(m);
        rep(i, 0, n) m[i][i] = min(m[i][i], ll(0));
        rep(k, 0, n) rep(i, 0, n) rep(j, 0, n) if (m[i][k] != inf && m[k][j] != inf)
        {
            auto newDist = max(m[i][k] + m[k][j], -inf);
            m[i][j] = min(m[i][j], newDist);
        }
        rep(k, 0, n) if (m[k][k] < 0) rep(i, 0, n) rep(j, 0, n) if (m[i][k] != inf && m[k][j] != inf) m[i][j] = -inf;
    }
} // namespace graph 
