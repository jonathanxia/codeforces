#include "common.h"

class SparseTable {
public:
    vector<vector<ll>> table;
    vector<ll> logTable;
    vector<ll> arrSize;
    function<ll(ll, ll)> operation;

    SparseTable(const vector<ll>& arr, function<ll(ll, ll)> op)
    {
        ll n = arr.size();
        ll logn = log2(n) + 1;

        table.resize(n, vector<ll>(logn));
        logTable.resize(n + 1);
        arrSize.resize(n + 1);
        operation = op;

        // Precompute logarithm values and array sizes
        for (int i = 2; i <= n; i++) {
            logTable[i] = logTable[i / 2] + 1;
            arrSize[i] = arrSize[i / 2] + (i & 1);
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

// int main() {
//     SparseTable st({3, 5, 1, 4, 2}, [](ll a, ll b) {return min(a, b);});
//     print(st.query(2, 4));
// }
