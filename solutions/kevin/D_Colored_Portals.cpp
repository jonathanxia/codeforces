// Link: https://codeforces.com/contest/2004/problem/D

#include<lib/macros.h>
#include<lib/print.h>
#include<lib/inp.h>
#include<lib/common.h>
#include<lib/cum.h>
#include<lib/string/util.h>
#include<lib/str.h>
#include<lib/vv/min.h>

void solve()
{
    ll n;
    ll q;
    cin >> n >> q;
    vpl queries(q);
    vstr types(n);
    cin >> types;
    cin >> queries;
    vl masks = LC(str::char_bitset(x), x, types);

    vstr portals { "BG", "BR", "BY", "GR", "GY", "RY" };
    vl portals_masks = LC(str::char_bitset(x), x, portals);

    umap<ll, cum::min<ll>> right;
    umap<ll, cum::max<ll>> left;
    foreach (mask, portals_masks) {
        vl lbase = RC(masks[i] == mask ? i : (ll)-1e18, i, 0ll, n - 1);
        vl rbase = RC(masks[i] == mask ? i : (ll)1e18, i, 0ll, n - 1);
        left.try_emplace(mask, lbase);
        right.try_emplace(mask, rbase);
    }

    walk(i, portals)
    {
        dprint(portals[i], left[portals_masks[i]]);
        dprint(portals[i], right[portals_masks[i]]);
    }

    foreachp(x, y, queries)
    {
        x--;
        y--;
        if (masks[x] & masks[y]) {
            print(abs(x - y));
            continue;
        }
        ll mini = 1e18;
        foreachp(mask, cumm, left)
        {
            if (mask & masks[x] && mask & masks[y]) {
                ll dist = abs(cumm.prefix(x) - x);
                dist += abs(cumm.prefix(x) - y);
                chkmin(mini, dist);
            }
        }
        foreachp(mask, cumm, right)
        {
            if (mask & masks[x] && mask & masks[y]) {
                ll dist = abs(cumm.suffix(x) - x);
                dist += abs(cumm.suffix(x) - y);
                chkmin(mini, dist);
            }
        }
        if (mini == 1e18) {
            print(-1);
        } else {
            print(mini);
        }
    }
}

int main()
{
    init();
    int t;
    cin >> t;
    cep(t) solve();
    return 0;
}