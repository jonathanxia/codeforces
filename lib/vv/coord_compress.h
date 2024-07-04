#pragma once
#include <lib/common.h>

namespace vv {
    template <typename T>
    vector<ll> coord_compress(const vector<T>& a, bool dedupe = true)
    {
        if(dedupe)
        {
            vi s_idx = argsort(a);
            umap<T, ll> coord;
            ll idx = 0;
            foreach(xi, s_idx) {
                T x = a[xi];
                if (coord.count(x) == 0) {
                    coord[x] = idx;
                    idx++;
                }
            }
            vl result(len(a));
            walk(i, a) {
                result[i] = coord[a[i]];
            }
            return result;
        }
        else
        {
            return to_vl(argsort(argsort(a)));
        }
    }
}