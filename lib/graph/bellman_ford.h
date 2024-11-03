#pragma once
#include<lib/common.h>

namespace kactl {
    const ll inf = LLONG_MAX;
    template <typename T = ll>
    struct Ed {
        ll a, b;
        T w;
        int s() { return a < b ? a : -a; }
    };
    template <typename T = ll>
    struct Node {
        T dist = inf;
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
template <typename T = ll>
struct BellmanFord {
    using Ed=kactl::Ed<T>;
    using Node=kactl::Node<T>;
    using vvplT = vector<vector<pair<ll, T>>>;

    vector<Node> nodes;
    vector<Ed> edges;
    int start;
    bool has_negative_cycle;

    BellmanFord(const vvplT& graph, int start_) : nodes(len(graph)) {
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
        T inf = kactl::inf;
        nodes[s].dist = 0;
        sort(ALL(eds), [](Ed a, Ed b)
             { return a.s() < b.s(); });

        int lim = len(nodes) / 2 + 2; // /3+100 with shuffled vertices
        rep(i, 0, lim) for (Ed ed : eds)
        {
            Node cur = nodes[ed.a], &dest = nodes[ed.b];
            if (abs(cur.dist) == inf)
                continue;
            T d = cur.dist + ed.w;
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

