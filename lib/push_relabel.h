#include <lib/common.h>

struct PushRelabel {
    struct Edge {
        int dest, back;
        ll f, c;
        Edge(int _dest, int _back, ll _f, ll _c)
            : dest(_dest)
            , back(_back)
            , f(_f)
            , c(_c)
        {
        }
    };
    vector<vector<Edge>> g;
    vector<ll> ec;
    vector<Edge*> cur;
    vector<vi> hs;
    vi H;
    PushRelabel(int n)
        : g(n)
        , ec(n)
        , cur(n)
        , hs(2 * n)
        , H(n)
    {
    }

    void addEdge(int s, int t, ll cap, ll rcap = 0)
    {
        if (s == t)
            return;
        g[s].push_back({ t, len(g[t]), 0, cap });
        g[t].push_back({ s, len(g[s]) - 1, 0, rcap });
    }

    void addFlow(Edge& e, ll f)
    {
        Edge& back = g[e.dest][e.back];
        if (!ec[e.dest] && f)
            hs[H[e.dest]].push_back(e.dest);
        e.f += f;
        e.c -= f;
        ec[e.dest] += f;
        back.f -= f;
        back.c += f;
        ec[back.dest] -= f;
    }
    ll calc(int s, int t)
    {
        int v = len(g);
        H[s] = v;
        ec[t] = 1;
        vi co(2 * v);
        co[0] = v - 1;
        repe(i, 0, v) cur[i] = g[i].data();
        for (Edge& e : g[s])
            addFlow(e, e.c);

        for (int hi = 0;;) {
            while (hs[hi].empty())
                if (!hi--)
                    return -ec[s];
            int u = hs[hi].back();
            hs[hi].pop_back();
            while (ec[u] > 0) // discharge u
                if (cur[u] == g[u].data() + len(g[u])) {
                    H[u] = 1e9;
                    for (Edge& e : g[u])
                        if (e.c && H[u] > H[e.dest] + 1)
                            H[u] = H[e.dest] + 1, cur[u] = &e;
                    if (++co[H[u]], !--co[hi] && hi < v)
                        repe(i, 0, v) if (hi < H[i] && H[i] < v)-- co[H[i]], H[i] = v + 1;
                    hi = H[u];
                } else if (cur[u]->c && H[u] == H[cur[u]->dest] + 1)
                    addFlow(*cur[u], min(ec[u], cur[u]->c));
                else
                    ++cur[u];
        }
    }
    bool leftOfMinCut(int a) { return H[a] >= len(g); }
};