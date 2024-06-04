#pragma once

#include <lib/common.h>
#include <lib/commit_dsu.h>
#include <lib/mset.h>

/**
 * Function that breaks the undirected graph into a collection of Eulerian tours
 * and paths. An Eulerian tour is a traversal through the graph that covers
 * every edge exactly once. It is known that a connected graph with 2k vertices of
 * odd degree can be decomposed into k Eulerian paths. If k = 0, then
 * one can form an Eulerian tour.
 * 
 * This function returns those k paths as a vector<vector<int>>.
 * Each path is of the form
 *    v[0], v[1], v[2], ..., v[n]
 * 
 * which represents the Eulerian traversal. If it starts and ends at the same place,
 * then v[0] == v[n], meaning that the last vertex is repeated. Otherwise, this is just
 * a regular path.
 * 
 * This function should fully handle
 *  1. Multi edges and self loops
 *  2. The case where adjList is disconnected
 * 
 * Usage: 
 *  https://codesprintla24.kattis.com/contests/codesprintla24open/submissions/13774050
*/
namespace graph {
vector<vector<int>> findEulerianToursAndPaths(vvpl& adjList) {
    int n = adjList.size();

    // Gather the connected components
    DSU dsu(n); FOR(u, 0, n - 1) foreachp(v, w, adjList[u]) dsu.unite(u, v);

    // Set up the graph object. We need to use multiset so we can delete edges
    vector<multiset<int>> graph(n);
    FOR(u, 0, n - 1) {
        foreachp(v, w, adjList[u]) {
            graph[u].insert(v);
            if (v == u) graph[u].insert(v); // Double count self loops
        }
    }
 
    // Find the odd degree vertices and introduce fictitious edges
    // between them, within each component.
    umap<ll, vi> odd_deg_vertices; // component -> odd deg vertices
    FOR(u, 0, n - 1) if (len(graph[u]) % 2 == 1) {
        odd_deg_vertices[dsu.find(u)].pb(u);
    }

    // We now add the fake edges and record which edges that
    // need to be deleted later
    auto norm_edge = [&](int u, int v) {
        return mp(min(u, v), max(u, v));
    };
    multiset<pi> edges_to_remove;
    foreachp(cc, verts, odd_deg_vertices) {
        assert(len(verts) % 2 == 0);
        while (verts.size() > 2) {
            ll u = verts.back(); verts.pop_back();
            ll v = verts.back(); verts.pop_back();
            graph[u].insert(v); graph[v].insert(u);
            edges_to_remove.insert(norm_edge(u, v));
        }
    }

    // Generic function to actually find Eulerian path or cycle
    auto findEulerianPathFrom = [&](int start) {
        stack<int> currentPath;
        vector<int> eulerianPath;
        currentPath.push(start);

        while (!currentPath.empty()) {
            int v = currentPath.top();
            if (!graph[v].empty()) {
                int u = *graph[v].begin();
                currentPath.push(u);
                mset::del(graph[v], u);
                mset::del(graph[u], v);
            } else {
                eulerianPath.push_back(v);
                currentPath.pop();
            }
        }
        return eulerianPath;
    };

    vvi output; // The final answer


    // At this point, each connected component either has two odd
    // vertices or zero odd vertices. Let's handle those with two
    // odd vertices first
    foreachp(cc, verts, odd_deg_vertices) {
        vi path = findEulerianPathFrom(verts[0]);
        reverse(ALL(path));

        vi cur_path;
        cur_path.push_back(path[0]);
        // Walk along the path until we hit something we are about
        // to add a bad edge
        FOR(i, 1, len(path) - 1) {
            auto edge = norm_edge(path[i], path[i - 1]);
            if (edges_to_remove.count(edge)) {
                mset::del(edges_to_remove, edge);
                output.push_back(cur_path);
                cur_path.clear();
            }
            cur_path.push_back(path[i]);
        }
        if (cur_path.size()) output.push_back(cur_path);
    }

    // Now deal with the rest of the cycles
    for (int i = 0; i < n; ++i) {
        if (!graph[i].empty()) {
            vi path = findEulerianPathFrom(i);
            if (len(path)) output.push_back(path);
        }
    }

    return output;
}

} // namespace graph