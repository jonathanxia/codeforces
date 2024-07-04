#pragma once
#include <lib/common.h>
namespace vv {
template <typename T>
vector<pair<T, ll>> with_idx(const vector<T>& a)
{
    vector<pair<T, ll>> out;
    ll n = len(a);
    FOR(i, 0, n - 1)
    {
        out.pb(mp(a[i], i));
    }
    return out;
}


}