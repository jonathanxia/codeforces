#pragma once
#include <lib/tree/ancestor_tree.h>

// Data structure for efficient range queries on the tree.
template <typename T>
struct BinaryLiftingTree {
    const AncestorTree& ast;
    vector<vector<T>> cumulative;

    function<T(T, T)> merge_func;

    BinaryLiftingTree(const DfsTree& tree, const AncestorTree& ast_, const vector<T>& values, function<T(T, T)> merge_func_)
        : ast(ast_), merge_func(merge_func_)
    {
        ll log_depth = ast.log_depth;
        ll n = tree.n;

        cumulative = vector<vector<T>>(log_depth, vector<T>(n));

        FOR(i, 0, n - 1) {
            cumulative[0][i] = values[i];
        }

        FOR(i, 1, log_depth - 1) {
            FOR(vert, 0, n - 1) {
                ll kp = ast.ancestors[i - 1][vert];
                cumulative[i][vert] = merge_func(cumulative[i - 1][vert], cumulative[i - 1][kp]);
            }
        }
    }

    BinaryLiftingTree(const DfsTree& tree, const vector<T>& values, function<T(T, T)> merge_func_) :
        BinaryLiftingTree(tree, AncestorTree(tree), values, merge_func_)
    {

    }

    // query(k, v) returns the merge func applied
    // on the nodes from v to the k-th ancestor of v,
    // inclusive. So k=0 means get the value itself

    // This version takes log time because it doesn't assume
    // idempotency
    T query(ll k, ll v) const {
        T ans = cumulative[0][v];
        v = ast.ancestors[0][v];

        FOR(i, 0, ast.log_depth - 1) {
            if ((1LL << i) > k) break;
            if ((1LL << i) & k) {
                ans = merge_func(ans, cumulative[i][v]);
                v = ast.ancestors[i][v];
            }
        }

        return ans;
    }

    // Performs o(1) time query by assuming idempotency
    T query1(ll k, ll v) const {
        T ans = cumulative[0][v];
        v = ast.ancestors[0][v];
        if (k == 0) return ans;

        // We must be very careful here, because the
        // cumulative queries are off by one

        // We want v + 1 -> v + k, inclusive
        // which means we want v + 1 -> v + 2^j union v + k - (2^j - 1) -> v + k
        // this requires 2^j >= k - 2^j + 1 --> 2^(j + 1) >= k + 1
        // but also 2^j <= k

        ll J = 1; // = 2^j
        ll j = 0;
        while (2 * J < k + 1) {
            J *= 2; j++;
        }

        ll v1 = ast.get_ancestor(k - J, v);
        return merge_func(ans, merge_func(cumulative[j][v], cumulative[j][v1]));
    }
};
