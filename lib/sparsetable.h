#pragma once
#include <lib/common.h>

template <typename T>
struct SparseTable {
public:
    vector<vector<T>> table;
    vector<ll> logTable;
    function<T(T, T)> operation;

    SparseTable(const vector<T>& arr, function<T(T, T)> op)
    {
        ll n = arr.size();
        ll logn = log2(int(n)) + 1;

        table.resize(n, vector<T>(logn));
        logTable.resize(n + 1);
        operation = op;

        // Precompute logarithm values and array sizes
        for (int i = 2; i <= n; i++) {
            logTable[i] = logTable[i / 2] + 1;
        }

        // Initialize the first column of the table
        for (int i = 0; i < n; i++) {
            table[i][0] = arr[i];
        }

        // Compute the rest of the table using dynamic programming
        for (int j = 1; (1 << j) <= n; j++) {
            for (int i = 0; (i + (1 << j) - 1) < n; i++) {
                table[i][j] = operation(table[i][j - 1], table[i + (1 << (j - 1))][j - 1]);
            }
        }
    }

    T query(int left, int right) const
    {
        ll k = logTable[right - left + 1];
        return operation(table[left][k], table[right - (1 << k) + 1][k]);
    }

    /* Works for non-idempotent operations, e.g. sum, product. Has log(n) query time*/
    T query_nonidempotent(int left, int right) const
    {
        T ans;
        bool first_loop = true;
        while (left <= right) {
            ll k = logTable[right - left + 1];
            T v = table[left][k];
            if (first_loop) {
                first_loop = false;
                ans = v;
            } else {
                ans = operation(ans, v);
            }
            left += (1L << k);
        }
        return ans;
    }
};

template <typename T>
struct MinSparseTable : SparseTable<T> {
    MinSparseTable(const vector<T>& v) : SparseTable<T>(
        v, [](T x, T y) {return min(x, y);}
    )
    {}
};

template <typename T>
struct MaxSparseTable : SparseTable<T> {
    MaxSparseTable(const vector<T>& v) : SparseTable<T>(
        v, [](T x, T y) {return max(x, y);}
    )
    {}
};
