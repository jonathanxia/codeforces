#pragma once
#include <lib/common.h>
/*
 * Given a weighted bipartite graph, matches every node on
 * the left with a node on the right such that no
 * nodes are in two matchings and the sum of the edge weights is minimal. Takes
 * cost[N][M], where cost[i][j] = cost for L[i] to be matched with R[j] and
 * returns (min cost, match), where L[i] is matched with
 * R[match[i]]. Negate costs for max cost. Requires $N \le M$.
 * Time: O(N^2M)
 */
pair<ll, vl> hungarian(const vvl& a)
{
    if (a.empty())
        return { 0, {} };
    ll n = len(a) + 1, m = len(a[0]) + 1;
    vl u(n), v(m), p(m), ans(n - 1);
    repe(i, 1, n)
    {
        p[0] = i;
        ll j0 = 0; // add "dummy" worker 0
        vl dist(m, INT64_MAX), pre(m, -1);
        vb done(m + 1);
        do { // dijkstra
            done[j0] = true;
            ll i0 = p[j0], j1, delta = INT64_MAX;
            repe(j, 1, m) if (!done[j])
            {
                auto cur = a[i0 - 1][j - 1] - u[i0] - v[j];
                if (cur < dist[j])
                    dist[j] = cur, pre[j] = j0;
                if (dist[j] < delta)
                    delta = dist[j], j1 = j;
            }
            repe(j, 0, m)
            {
                if (done[j])
                    u[p[j]] += delta, v[j] -= delta;
                else
                    dist[j] -= delta;
            }
            j0 = j1;
        } while (p[j0]);
        while (j0) { // update alternating path
            ll j1 = pre[j0];
            p[j0] = p[j1], j0 = j1;
        }
    }
    repe(j, 1, m) if (p[j]) ans[p[j] - 1] = j - 1;
    return { -v[0], ans }; // min cost
}