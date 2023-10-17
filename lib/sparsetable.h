#include <lib/common.h>

template <typename T>
class SparseTable {
public:
    vector<vector<T>> table;
    vector<ll> logTable;
    function<T(T, T)> operation;

    SparseTable(const vector<T>& arr, function<T(T, T)> op)
    {
        ll n = arr.size();
        ll logn = log2(n) + 1;

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

    ll query(int left, int right)
    {
        ll k = logTable[right - left + 1];
        return operation(table[left][k], table[right - (1 << k) + 1][k]);
    }
};

