#include "common.h"

// Input
namespace inp {
long long binary()
{
    string s;
    cin >> s;
    long long res = 0;
    for (char c : s) {
        res <<= 1;
        if (c == '1')
            res |= 1;
    }
    return res;
}

void array(vl& arr, int n)
{
    rep(i, 0, n - 1)
    {
        cin >> arr[i];
    }
}

void array(vi& arr, int n)
{
    rep(i, 0, n - 1)
    {
        cin >> arr[i];
    }
}

void array1(vl& arr, int n)
{
    rep(i, 1, n)
    {
        cin >> arr[i];
    }
}

}
