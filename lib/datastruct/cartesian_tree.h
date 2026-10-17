#pragma once
#include <lib/common.h>

/**
 * Cartesian tree of a in O(n); node i = index i. Described for the max tree
 * (MinCartesianTree: same, with min). Equal values: the leftmost is higher.
 *
 * root           index of the max of a (-1 if a is empty)
 * parent[i]      parent of i (-1 for root)
 * range_left[i]  i's subtree is exactly a[range_left[i], range_right[i]] (inclusive):
 * range_right[i]   the widest range around i in which a[i] is the leftmost max
 * left_child[i]  index of the max of a[range_left[i], i-1] (-1 if empty)
 * right_child[i] index of the max of a[i+1, range_right[i]] (-1 if empty)
 * size(i)        subtree size of i
 *
 * Custom order: CartesianTree<T, better> with bool better(T x, T y) = x goes above
 * y, false for equal values.
 */
template <typename T, bool (*better)(T, T)>
struct CartesianTree {
    int n, root;
    vi parent, left_child, right_child;
    vi range_left, range_right;

    CartesianTree(const vector<T>& a)
        : n(len(a)), root(-1), parent(n, -1), left_child(n, -1), right_child(n, -1),
          range_left(n), range_right(n, n - 1)
    {
        vi st;
        FOR(i, 0, n - 1) {
            int last = -1;
            while (!st.empty() && better(a[i], a[st.back()])) {
                last = st.back();
                st.pop_back();
                range_right[last] = i - 1;
            }
            left_child[i] = last;
            if (last != -1) parent[last] = i;
            if (!st.empty()) {
                right_child[st.back()] = i;
                parent[i] = st.back();
            }
            range_left[i] = st.empty() ? 0 : st.back() + 1;
            st.push_back(i);
        }
        if (n > 0) root = st[0];
    }

    int size(int i) const { return range_right[i] - range_left[i] + 1; }
};

template <typename T> bool cartesian_greater(T x, T y) { return x > y; }
template <typename T> bool cartesian_less(T x, T y) { return x < y; }

template <typename T> using MaxCartesianTree = CartesianTree<T, cartesian_greater<T>>;
template <typename T> using MinCartesianTree = CartesianTree<T, cartesian_less<T>>;
