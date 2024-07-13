#pragma once
#include <lib/common.h>

namespace tree {
    void centroid_dfs(int node, int parent, const vector<vector<pair<ll, ll>>> &adj, vector<int> &subtreeSize) {
        subtreeSize[node] = 1;
        for (const auto &neighbor : adj[node]) {
            int next = neighbor.first;
            if (next == parent) continue;
            centroid_dfs(next, node, adj, subtreeSize);
            subtreeSize[node] += subtreeSize[next];
        }
    }

    void findCentroids(int node, int parent, const vector<vector<pair<ll, ll>>> &adj, vector<int> &subtreeSize, int n, vector<int> &centroids) {
        int heaviestChildSize = 0;

        for (const auto &neighbor : adj[node]) {
            int next = neighbor.first;
            if (next == parent) continue;
            findCentroids(next, node, adj, subtreeSize, n, centroids);
            heaviestChildSize = max(heaviestChildSize, subtreeSize[next]);
        }

        heaviestChildSize = max(heaviestChildSize, n - subtreeSize[node]);
        if (heaviestChildSize <= n / 2) {
            centroids.push_back(node);
        }
    }

    vector<int> getCentroids(const vector<vector<pair<ll, ll>>> &adj) {
        int n = adj.size();
        vector<int> subtreeSize(n, 0);
        vector<int> centroids;

        // Start DFS from node 0 (assuming nodes are 0-indexed)
        centroid_dfs(0, -1, adj, subtreeSize);
        findCentroids(0, -1, adj, subtreeSize, n, centroids);

        return centroids;
    }
} // namespace graph