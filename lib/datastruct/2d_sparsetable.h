#pragma once
#include <lib/common.h>

template<typename T>
struct SparseTable2D {
    vector<vector<vector<vector<T>>>> table; int n, m;
    function<T(T, T)> merge_function;

    void buildSparseTable(const vector<vector<T>>& input) {
        int log_n = log2(n) + 1;
        int log_m = log2(m) + 1;
        dbg(n);
        dbg(m);

        table.assign(n, vector<vector<vector<T>>>(m, vector<vector<T>>(log_n, vector<T>(log_m))));

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                table[i][j][0][0] = input[i][j];
            }
        }

        for (int k = 0; k < log_n; ++k) {
            for (int l = 0; l < log_m; ++l) {
                for (int i = 0; i < n; ++i) {
                    for (int j = 0; j < m; ++j) {
                        if (k > 0) {
                            table[i][j][k][l] = merge_function(table[i][j][k - 1][l], table[min(i + (1 << (k - 1)), n - 1)][j][k - 1][l]);
                        }
                        if (l > 0) {
                            table[i][j][k][l] = merge_function(table[i][j][k][l - 1], table[i][min(j + (1 << (l - 1)), m - 1)][k][l - 1]);
                        }
                    }
                }
            }
        }
    }

    SparseTable2D(const vector<vector<T>>& input, function<T(const T&, const T&)> merge_function_) 
        : merge_function(merge_function_) {
        n = input.size();
        m = input[0].size();
        buildSparseTable(input);
    }

    T query(int x1, int y1, int x2, int y2) {
        int len_x = x2 - x1 + 1;
        int len_y = y2 - y1 + 1;
        int kx = log2(len_x);
        int ky = log2(len_y);

        T result = table[x1][y1][kx][ky];

        result = merge_function(result, table[x2 - (1 << kx) + 1][y1][kx][ky]);
        result = merge_function(result, table[x1][y2 - (1 << ky) + 1][kx][ky]);
        result = merge_function(result, table[x2 - (1 << kx) + 1][y2 - (1 << ky) + 1][kx][ky]);

        return result;
    }
};