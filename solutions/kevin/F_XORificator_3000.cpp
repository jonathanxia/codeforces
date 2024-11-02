// Link: https://codeforces.com/contest/2036/problem/F

#include<lib/macros.h>
#include<lib/print.h>
#include<lib/inp.h>
#include<lib/common.h>
#include<lib/bitster.h>
#include<lib/bitster/prefix_xor.h>

void solve()
{
    ll l, r, i, k;
    cin >> l >> r >> i >> k;

    auto solve_prefix = [&](ll query) -> ll {
        ll prefix_all = bitster::prefix_xor(query);
        // find the largest k mod 2^i smaller than or equal to query
        ll num = largest_st(j, k + (1LL << i) * j <= query, 0, (1LL << (62 - i)));
        if (num & 1) {
            prefix_all ^= k;
        }
        prefix_all ^= bitster::prefix_xor(num) << i;
        return prefix_all;
    };
    print(solve_prefix(r) ^ solve_prefix(l - 1));
}

int main()
{
    init();
    int t;
    cin >> t;
    cep(t) solve();
    return 0;
}