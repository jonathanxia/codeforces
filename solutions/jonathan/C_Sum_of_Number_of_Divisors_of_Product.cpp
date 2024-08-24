// Link: https://atcoder.jp/contests/arc182/tasks/arc182_c
#include <lib/constants/mod998244353.h>
#include <lib/mod_int.h>
#include <lib/matrix.h>
#include <lib/nt.h>

/**
 * Goal: compute number of ways to pick one block from each pile, after placing down the blocks
 * 
 * dp[i + 1, S'] = foreach subset S, dp[i, S] * prod of exponents(x) in S' \ S
 * 
 * However, the transition can also pick a different x each time
 * so it is really the sum of these transitions across all x
 * 
 * Matrix m wants to be computed as
 * (1 + M + M^2 + ... + M^n)v
 * 
 */

void solve() {
    ll n, m;
    cin >> n >> m;
    matrix<MI> mat(64, 64);
    FOR(x, 1, m)
    {
        auto factors = nt::primeFactorization(x);
        FOR(sp, 0, 63)
        {
            foreach_subset(s, sp)
            {
                ll remaining_mask = sp ^ s;
                ll coeff = 1;
                FOR(b, 0, 5) if (nt::get_bit(remaining_mask, b)) {
                    coeff *= factors[nt::primes[b]];
                }
                mat(sp, s) += coeff;
            }
        }
    }

    // Now we want the initial vector of the dp
    matrix<MI> v(64, 1, 1);

    matrix<MI> big_mat = linalg::block_matrix<MI>({
        {mat, v},
        {matrix<MI>(1, 64, 0), matrix<MI>(1, 1, 1)},
    });
    // M v
    // 0 1

    big_mat = linalg::pow(big_mat, n);
    auto res = big_mat * matrix<MI>(65, 1, 1);
    print(res(63, 0) - 1);

}

int main() {
    init();
    nt::do_sieve(16);
    solve();
    return 0;
}