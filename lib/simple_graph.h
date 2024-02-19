#pragma once
#include <lib/common.h>

// Empty struct to use in templates
struct EMPTY {};

// Adjacency-List style graph which stores per-node information
template<typename Node=EMPTY>
struct SimpleGraph {
    int nodes;
    int edges;
    vector<vi> adj;
    vector<Node> data;

    SimpleGraph(int nodes) : nodes(nodes) {
        adj = vector<vi>(nodes);
        data = vector<Node>(nodes);
        edges = 0;
    }

    Node& operator[](int x) {
        return data[x];
    }

    void add_edge(int u, int v) {
        adj[u].push_back(v);
    }

    void read_edges(int num_edges, bool directed=false) {
        FOR(i, 1, num_edges) {
            int u, v;
            cin >> u >> v;
            add_edge(u, v);
            if (not directed) {
                add_edge(v, u);
            }
            edges++;
        }
    }

    vi postorder() {
        vi result;
        vi seen(nodes);
        function<void(int)> dfs = [&](int x) {
            if (seen[x]) return;
            seen[x] = 1;
            foreach(w, adj[x])
                dfs(w);
            result.push_back(x);
        };
        FOR(i, 0, nodes-1) dfs(i);
        return result;
    }

    SimpleGraph<Node> reversed() {
        SimpleGraph<Node> result(nodes);
        FOR(u, 0, nodes-1) foreach(v, adj[u]) result.add_edge(v, u);
        return result;
    }

    vi toposort() {
        vi po = postorder();
        reverse(ALL(po));
        return po;
    }

    SimpleGraph<vi> scc_graph() {
        auto rg = this->reversed();
        vi po = rg.postorder();
        reverse(ALL(po));

        int cur_scc = 0;
        vi scc(nodes, -1);
        vector<vi> scc2nodes;
        set<pi> edges;
        function<void(int, int)> dfs = [&](int x, int SCC) {
            if (scc[x] != -1) {
                if (scc[x] != SCC) // no self loops
                    edges.emplace(SCC, scc[x]);
                return;
            }
            scc[x] = SCC;
            scc2nodes.back().push_back(x);
            foreach(w, adj[x])
                dfs(w, SCC);
        };
        foreach(x, po) if(scc[x] == -1) {
            scc2nodes.emplace_back();
            dfs(x, cur_scc);
            cur_scc++;
        }

        SimpleGraph<vi> sccg(cur_scc);
        foreachp(u, v, edges)
            sccg.add_edge(u, v);
        FOR(scc, 0, cur_scc-1)
            sccg[scc] = scc2nodes[scc];
        return sccg;
    }
};