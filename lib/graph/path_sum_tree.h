#pragma once
#include <atcoder/lazysegtree>
#include <lib/common.h>
#include <lib/dfs.h>

/**
 * Performs path aggregations on a tree that also supports
 * editing
*/
namespace path_sum_tree {
    template <typename T>
    struct S {
        T data;
        ll sz;
    };

    template <typename T>
    S<T> op(S<T> l, S<T> r) {
        return {l.data + r.data, l.sz + r.sz};
    }

    template <typename T>
    S<T> e() { return S<T>{0, 1}; }

    template <typename T>
    S<T> mapping(T l, S<T> r) {
        if (l == T(0)) return r;
        return {r.data + r.sz * l, r.sz};
    }
    template <typename F>
    F composition(F l, F r) { return l + r; }
    template <typename F>
    F id() { return 0; }

    template <typename T>
    struct PathSumTree {
        LCATree lca_tree;
        atcoder::lazy_segtree<S<T>, op<T>, e<T>, T, mapping<T>, composition<T>, id<T>> seg;

        PathSumTree() {}
        PathSumTree(const LCATree& lca_tree_) : lca_tree(lca_tree_), seg(lca_tree.forest.n) {}
        PathSumTree(const LCATree& lca_tree_, const vector<T>& vals) : PathSumTree(lca_tree_) {
            walk(node, vals) {
                update(node, vals[node]);
            }
        }

        T root_query(ll node) {
            // Query the sum from node to the root
            return seg.get(lca_tree.forest.node_to_counter[node]).data;
        }

        T query(ll u, ll v) {
            ll lca = lca_tree.lca(u, v);
            T ans = root_query(u) + root_query(v);
            ans -= root_query(lca);
            if (lca_tree.forest.parent[lca] >= 0) {
                ans -= root_query(lca_tree.forest.parent[lca]);
            }
            return ans;
        }

        void update(ll node, T value) {
            const DfsTree& tree = lca_tree.forest;
            ll count = tree.node_to_counter[node];
            seg.update(count, count + tree.num_desc[node] - 1, value);
        }
    };
} // namespace path_sum_tree
using path_sum_tree::PathSumTree;

