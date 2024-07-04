#pragma once
#include<lib/common.h>

namespace kactl {
    const ll inf = LLONG_MAX;
    struct Ed {
        int a, b;
        ll w;
        int s() { return a < b ? a : -a; }
    };
    struct Node {
        ll dist = inf;
        int prev = -1;
    };
}

/**
 * Source: kactl
 * Description: Calculates shortest paths from $s$ in a graph that might have negative edge weights.
 * Unreachable nodes get dist = inf; nodes reachable through negative-weight cycles get dist = -inf.
 * Assumes $V^2 \max |w_i| < \tilde{} 2^{63}$.
 * Time: O(VE)
 * Usage: https://atcoder.jp/contests/arc173/submissions/51168857
 */
struct BellmanFord {
    using Ed=kactl::Ed;
    using Node=kactl::Node;

    vector<Node> nodes;
    vector<Ed> edges;
    int start;
    bool has_negative_cycle;

    BellmanFord(const vvpl& graph, int start_) : nodes(len(graph)) {
        start = start_;
        walk(u, graph) {
            foreachp(v, w, graph[u]) {
                edges.push_back(Ed{u, v, w});
            }
        }
        has_negative_cycle = false;
        runBellmanFord(nodes, edges, start);
    }

    void runBellmanFord(vector<Node> &nodes, vector<Ed> &eds, int s)
    {
        ll inf = kactl::inf;
        nodes[s].dist = 0;
        sort(ALL(eds), [](Ed a, Ed b)
             { return a.s() < b.s(); });

        int lim = len(nodes) / 2 + 2; // /3+100 with shuffled vertices
        rep(i, 0, lim) for (Ed ed : eds)
        {
            Node cur = nodes[ed.a], &dest = nodes[ed.b];
            if (abs(cur.dist) == inf)
                continue;
            ll d = cur.dist + ed.w;
            if (d < dest.dist)
            {
                dest.prev = ed.a;
                dest.dist = (i < lim - 1 ? d : -inf);
            }
        }
        rep(i, 0, lim) for (Ed e : eds)
        {
            if (nodes[e.a].dist == -inf) {
                nodes[e.b].dist = -inf;
                has_negative_cycle = true;
            }
        }
    }

    vi extract_negative_cycle() {
        vi output;
        if (!has_negative_cycle) {
            return output;
        }
        ll p = -1;
        ll n = len(nodes);
        for (int i = 0; i < n; i++) {
            if (nodes[i].dist == -kactl::inf) {
                p = i;
                break;
            }
        }
        for (int i = 0; i < n; i++) {
            p = nodes[p].prev;
        }

        ll q = p;
        while (true) {
            output.pb(q);
            q = nodes[q].prev;
            if (q == p) break;
        }
        reverse(ALL(output));
        return output;
    }
};

