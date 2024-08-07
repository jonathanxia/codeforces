// Link: https://codeforces.com/contest/1993/problem/C
#include <lib/vv/max.h>
#include<lib/print.h>
#include<lib/inp.h>
#include<lib/intervals.h>
#include<lib/macros.h>
#include<lib/common.h>

void solve()
{
    ll n, k;
    cin >> n >> k;
    vl a(n);
    cin >> a;

    // common moment either happens in left half or right half of [0, 2k]
    vpl left;
    vpl right;

    foreach (chip, a) {
        ll offset = chip % (2 * k);
        if (offset < k) {
            left.emplace_back(offset, k - 1);
            right.emplace_back(k, offset + k - 1);
        } else {
            left.emplace_back(0, offset - k - 1);
            right.emplace_back(offset, 2 * k - 1);
        }
    }

    auto [leftgood, leftlr] = intervals::intersection(left);
    auto [rightgood, rightlr] = intervals::intersection(right);
    ll leftl = leftlr.first;
    ll rightl = rightlr.first;
    ll leftbest = 1e18;
    ll rightbest = 1e18;
    if (!leftgood && !rightgood) {
        print(-1);
        return;
    }
    if (leftgood) {
        rep(i, vv::max(a), vv::max(a) + 2 * k)
        {
            if (i % (2 * k) == leftl) {
                leftbest = i;
                break;
            }
        }
    }
    if (rightgood) {
        rep(i, vv::max(a), vv::max(a) + 2 * k)
        {
            dprint(i % (2 * k));
            if (i % (2 * k) == rightl) {
                rightbest = i;
                break;
            }
        }
    }
    print(min(rightbest, leftbest));
}

int main()
{
    init();
    int t;
    cin >> t;
    cep(t) solve();
    return 0;
}