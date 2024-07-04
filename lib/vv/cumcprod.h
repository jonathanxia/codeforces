#pragma once
#include <lib/common.h>
namespace vv {
vl cumcprod(const vl& a, bool reverse = false)
{
    vl ret(a);
    ll n = len(a);
    if (reverse) {
        DOR(i, n - 2, 0)
        {
            ret[i] = cmul(ret[i + 1], ret[i]);
        }
    } else {
        FOR(i, 1, n - 1)
        {
            ret[i] = cmul(ret[i - 1], ret[i]);
        }
    }
    return ret;
}


}