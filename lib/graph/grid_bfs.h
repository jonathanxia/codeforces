#pragma once
#include <lib/common.h>

namespace graph {
    // Runs bfs on a grid problem
    // Starts need to be passed in, can have multiple start points
    // allowed should be set to true if you just want to run BFS on the whole grid
    void grid_bfs(const vector<vb>& allowed, const vpl& starts, vvl& dist, ll default_dist = LLONG_MAX, bool allow_diag = false) {
        ll n = len(allowed);
        ll m = len(allowed[0]);

        FOR(i, 0, n - 1) FOR(j, 0, m - 1) dist[i][j] = -1;

        deque<pl> pq;
        foreach(s, starts) {
            if (!allowed[s.first][s.second]) continue;
            pq.push_back(s);
            dist[s.first][s.second] = 0;
        }

        while(len(pq)) {
            pl node = pq.front();
            pq.pop_front();

            // Process the node by adding its children
            FOR(dir, 0, 3 + 4 * allow_diag) {
                pl child = {node.first + dx[dir], node.second + dy[dir]};
                // Check if you step out of bounds
                if (!(ordered(0, child.first, n - 1) && ordered(0, child.second, m - 1))) continue;
                // Check if the child is allowed
                if (!allowed[child.first][child.second]) continue;
                if (dist[child.first][child.second] >= 0) continue;

                dist[child.first][child.second] = dist[node.first][node.second] + 1;
                pq.push_back(child);
            }
        }

        FOR(i, 0, n - 1) FOR(j, 0, m - 1) {
            dist[i][j] = dist[i][j] < 0 ? default_dist : dist[i][j];
        }
    }

    vvl grid_bfs(const vector<vb>& allowed, const vpl& starts, ll default_dist = LLONG_MAX, bool allow_diag = false) {
        ll n = len(allowed);
        ll m = len(allowed[0]);
        vvl dist(n, vl(m, -1));
        grid_bfs(allowed, starts, dist, default_dist, allow_diag);
        return dist;
    }
} // namespace graph
