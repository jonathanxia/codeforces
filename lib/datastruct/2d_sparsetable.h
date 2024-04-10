#pragma once
#include <lib/common.h>
#include <lib/datastruct/ndarray.h>


/**
 * 2d sparse table, where you query(row_start, row_end, col_start, col_end). Everything is
 * inclusive bounds.
 * 
 * Usage: https://atcoder.jp/contests/abc347/submissions/51834448
 * 
 *  vvl scores(n - m + 1, vl(n - m + 1));
    FOR(i, 0, n - m) FOR(j, 0, n - m) scores[i][j] = ...;

    SparseTable2D<ll> st(scores, [](ll x, ll y) { return max(x, y); });

    st.query(0, 4, 2, 3) (this is the box with corners (0, 2) and (4, 3))
*/
template<typename T>
struct SparseTable2D {
    int n, m;
    ndarray<T, 4> table;
    function<T(T, T)> merge_function;

    void buildSparseTable(const vector<vector<T>>& input) {
        int log_n = log2(n) + 1;
        int log_m = log2(m) + 1;

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                table(0, 0, i, j) = input[i][j];
            }
        }

        for (int k = 0; k < log_n; ++k) {
            for (int l = 0; l < log_m; ++l) {
                for (int i = 0; i < n; ++i) {
                    for (int j = 0; j < m; ++j) {
                        if (k > 0) {
                            table(k, l, i, j) = merge_function(table(k - 1, l, i, j), table(k - 1, l, min(i + (1 << (k - 1)), n - 1), j));
                        }
                        if (l > 0) {
                            table(k, l, i, j) = merge_function(table(k, l - 1, i, j), table(k, l - 1, i, min(j + (1 << (l - 1)), m - 1)));
                        }
                    }
                }
            }
        }
    }

    SparseTable2D(const vector<vector<T>>& input, function<T(const T&, const T&)> merge_function_)
        : n(len(input)), m(input[0].size()),
          table({int(log2(n) + 1), int(log2(m) + 1), n, m}),
          merge_function(merge_function_) {
        buildSparseTable(input);
    }

    T query(int x1, int x2, int y1, int y2) {
        int len_x = x2 - x1 + 1;
        int len_y = y2 - y1 + 1;
        int kx = log2(len_x);
        int ky = log2(len_y);

        T result = table(kx, ky, x1, y1);

        result = merge_function(result, table(kx, ky, x2 - (1 << kx) + 1, y1));
        result = merge_function(result, table(kx, ky, x1, y2 - (1 << ky) + 1));
        result = merge_function(result, table(kx, ky, x2 - (1 << kx) + 1, y2 - (1 << ky) + 1));

        return result;
    }
};

