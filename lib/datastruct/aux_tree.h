#pragma once
#include <lib/dfs.h>

/**
 * An aux tree (or virtual tree)
 *
 * Given a tree G, and some nodes that are marked red, the aux tree
 * is a compressed version of the tree that maintains the structure of the
 * red subset.
 *
 * Rigorously, it means that we preserve the LCA operation (under some arbitrary root).
 * Specifically, the aux tree is a subset S of nodes of G such that for every u, v \in S,
 * lca(u, v) \in S as well.
 *
 * Notably, if the number of red nodes is k, the size of the auxtree is at most 2k - 1, irrelevant
 * of the size of G.
 *
 * Inspired by radoslav11
 * 
 * Usage: https://codeforces.com/contest/1923/submission/248043301
 * 
 *  // vvl colors...
 *  DfsTree tree(graph, 0);
    LCATree lca_tree(tree);
    FOR(c, 1, n) {
        if (len(colors[c]) == 0) continue;
        AuxTree aux_tree(lca_tree, colors[c]);
        function<void(ll)> dfs = [&](ll node) {
            // stuff...
            foreach(child, aux_tree.vg[node]) {
                dfs(child);
            }
            // Post process
        };
        dfs(aux_tree.root);
    }
*/

struct AuxTree {
    const LCATree& lca_tree;
    ll n;

    vi mstack;

    /**
     * Output instance fields:
     *
     * vg: the virtual tree, where vg[node] is a list of all its children
     * root: this is the root of the tree, so start your DFS algorithms there.
     *
     * Note that vg needs to be a umap so that the size of vg is not O(n) but rather O(k)
    */
    umap<int, vi> vg;
    int root = -1;

    bool cmp(int u, int v) {
        return lca_tree.forest.node_to_counter[u] < lca_tree.forest.node_to_counter[v];
    }

    inline bool upper(int u, int v) {
        // Is v a descendant of u?
        ll cu = lca_tree.forest.node_to_counter[u];
        ll cv = lca_tree.forest.node_to_counter[v];

        return cu <= cv && cv <= cu + lca_tree.forest.num_desc[u] - 1;
    }

    /**
     * You need to run an LCA tree to precompute everything.
     *
     * vec should be the node numbers that are marked red.
    */
    AuxTree(const LCATree& lca_tree_, vector<int> vec) : lca_tree(lca_tree_) {
        n = lca_tree.forest.n;

        build_tree(vec);
    }

    void build_tree(vector<int>& vec)
    {
        if(vec.empty()) { root = -1; return; }

        auto cmp_ = [this](int u, int v) { return cmp(u, v); };
        sort(vec.begin(), vec.end(), cmp_);
        vec.erase(unique(vec.begin(), vec.end()), vec.end());

        int st_sz = vec.size();
        for(int i = 0; i + 1 < st_sz; i++)
            vec.push_back(lca_tree.lca(vec[i], vec[i + 1]));

        sort(vec.begin(), vec.end(), cmp_);
        vec.erase(unique(vec.begin(), vec.end()), vec.end());

        // for(int vertex: vec)
        //     vg[vertex].clear();

        mstack.push_back(vec[0]);

        for(int i = 1; i < (int)vec.size(); i++)
        {
            while(!upper(mstack.back(), vec[i]))
            {
                vg[mstack[len(mstack) - 2]].push_back(mstack.back());
                mstack.pop_back();
            }
            mstack.push_back(vec[i]);
        }

        for(int i = 0; i < len(mstack) - 1; i++)
            vg[mstack[i]].push_back(mstack[i + 1]);

        root = mstack[0];
    }
};

