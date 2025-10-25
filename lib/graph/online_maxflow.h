#pragma once
#include <lib/common.h>

struct OnlineMaxFlow {
    vvl graph;
    umap<pl, ll> weights;
    ll source = -1;
    ll sink = -1;
    ll total_flow = 0;

    ll add_node()
    {
        graph.emplace_back();
        return len(graph) - 1;
    }

    bool is_node(ll node)
    {
        return ordered(0, node, len(graph) - 1);
    }

    void set_source(ll node)
    {
        if (source != -1) {
            throw std::out_of_range("Source already set");
        } else if (!is_node(node)) {
            throw std::out_of_range("node out of range");
        }
        source = node;
    }

    void set_sink(ll node)
    {
        if (sink != -1) {
            throw std::out_of_range("Source already set");
        } else if (!is_node(node)) {
            throw std::out_of_range("node out of range");
        }
        sink = node;
    }

    void add_edge(ll u, ll v, ll w, bool bidirectional = false)
    {
        if (!is_node(u) || !is_node(v)) {
            throw std::out_of_range("Node out of range");
        }
        graph[u].pb(v);
        weights[{ u, v }] += w;
        weights.try_emplace({ v, u }, 0);
        if (bidirectional) {
            add_edge(v, u, w);
        }
    }

    // stops after flow_cap is reached
    ll max_flow(ll flow_cap = std::numeric_limits<ll>::max())
    {
        if (source == -1 || sink == -1) {
            throw std::out_of_range("Source and sink must be set to run max flow");
        }
        // Edmonds Karp
        while (total_flow < flow_cap) {
            // run BFS
            queue<ll> q;
            vl predecessor(len(graph), -1);
            vb processed(len(graph), false);
            q.push(source);
            while (!q.empty()) {
                ll node = q.front();
                if (node == sink)
                    break;
                q.pop();
                if (processed[node])
                    continue;
                processed[node] = true;
                foreach (child, graph[node]) {
                    if (weights[{ node, child }]) {
                        if (predecessor[child] == -1)
                            predecessor[child] = node;
                        q.push(child);
                    }
                }
            }

            // process path from source to sink
            if (predecessor[sink] == -1) {
                break;
            }
            ll flow = flow_cap;
            ll node = sink;
            while (node != source) {
                ll pred = predecessor[node];
                chkmin(flow, weights[{ pred, node }]);
                node = pred;
            }
            node = sink;
            while (node != source) {
                ll pred = predecessor[node];
                weights[{ pred, node }] -= flow;
                weights[{ node, pred }] += flow;
                node = pred;
            }
            total_flow += flow;
        }
        return total_flow;
    }
};