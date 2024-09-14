#pragma once

#include <lib/matrix.h>

namespace linalg {
    /**
     * Solves Ax = b
     * Returns a vector of solutions.
     * 
     * sol[0] = a particular solution
     * sol[1...] = basis for that solution
     * empty means no solution
     */
    template <typename T>
    vector<vector<T>> solve_linear(vector<vector<T>> A, vector<T> b, int n = -1, int m = -1) {
        if (n == -1) {
            n = len(A);
            assert(n > 0);
            m = len(A[0]);
        }
        assert(n == len(A) && n == len(b));
        int rk = 0;
        FOR(j, 0, m - 1) {
            if (rk == n) break;
            FOR(i, rk, n - 1) if (A[i][j] != 0) {
                swap(A[rk], A[i]);
                swap(b[rk], b[i]);
                break;
            }
            if (A[rk][j] == 0) continue;
            T c = T(1) / A[rk][j];
            for (auto&& x: A[rk]) x *= c;
            b[rk] *= c;
            FOR(i, 0, n - 1) if (i != rk) {
                T c = A[i][j];
                if (c == T(0)) continue;
                b[i] -= b[rk] * c;
                FOR(k, j, m - 1) { A[i][k] -= A[rk][k] * c; }
            }
            ++rk;
        }
        FOR(i, rk, n - 1) if (b[i] != 0) return {};
        vector<vector<T>> res(1, vector<T>(m));
        vector<int> pivot(m, -1);
        int p = 0;
        FOR(i, 0, rk - 1) {
            while (A[i][p] == 0) ++p;
            res[0][p] = b[i];
            pivot[p] = i;
        }
        FOR(j, 0, m - 1) if (pivot[j] == -1) {
            vector<T> x(m);
            x[j] = -1;
            FOR(k, 0, j - 1) if (pivot[k] != -1) x[k] = A[pivot[k]][j];
            res.emplace_back(x);
        }
        return res;
    }

    template <typename T>
    vector<vector<T>> solve_linear(const matrix<T>& A, const vector<T>& b, int n = -1, int m = -1) {
        vector<vector<T>> a(A.get_n_rows(), vector<T>(A.get_n_cols()));
        FOR(i, 0, A.get_n_rows() - 1) FOR(j, 0, A.get_n_cols() - 1) a[i][j] = A(i, j);
        return solve_linear(a, b, n, m);
    }
} // namespace linalg