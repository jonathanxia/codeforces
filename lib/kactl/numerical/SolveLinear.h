#pragma once
/**
 * Author: Per Austrin, Simon Lindholm
 * Date: 2004-02-08
 * License: CC0
 * Description: Solves $A * x = b$. If there are multiple solutions, an arbitrary one is returned.
 *  Returns rank, or -1 if no solutions. Data in $A$ and $b$ is lost.
 * Edit by Kevin Xia: pseudo-templatized to be compatible with Mod
 * Time: O(n^2 m)
 * Status: tested on kattis:equationsolver, and bruteforce-tested mod 3 and 5 for n,m <= 3
 */
#include <lib/common.h>

namespace kactl {
typedef double T; // change to whatever type you need
typedef vector<T> vT;

bool is_zero(T num){
	const double eps = 1e-12;
	return fabs(num) <= eps;
}

// If field T does not support operator>, just return !is_zero(b).
// Mainly used to prevent numerical instability
bool is_greater(T a, T b){
	return fabs(a) > fabs(b);
}

int solveLinear(vector<vT>& A, vT& b, vT& x) {
	int n = len(A), m = len(x), rank = 0, br, bc;
	if (n) assert(len(A[0]) == m);
	vi col(m); iota(ALL(col), 0);

	rep(i,0,n) {
		T v, bv = 0;
		rep(r,i,n) rep(c,i,m) {
			v = fabs(A[r][c]);
			if (is_greater(v, bv))
				br = r, bc = c, bv = v;
		}
		if (is_zero(bv)) {
			rep(j,i,n) if (!is_zero(b[j])) return -1;
			break;
		}
		swap(A[i], A[br]);
		swap(b[i], b[br]);
		swap(col[i], col[bc]);
		rep(j,0,n) swap(A[j][i], A[j][bc]);
		bv = 1/A[i][i];
		rep(j,i+1,n) {
			double fac = A[j][i] * bv;
			b[j] -= fac * b[i];
			rep(k,i+1,m) A[j][k] -= fac*A[i][k];
		}
		rank++;
	}

	// Erase this for loop part if you only care about the rank.
	x.assign(m, T(0));
	for (int i = rank; i--;) {
		b[i] /= A[i][i];
		x[col[i]] = b[i];
		rep(j,0,i) b[j] -= A[j][i] * b[i];
	}
	return rank; // (multiple solutions if rank < m)
}
}