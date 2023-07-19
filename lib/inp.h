#include <lib/macros.h>

// Input
namespace inp
{
    long long binary()
    {
        string s;
        cin >> s;
        long long res = 0;
        for (char c : s)
        {
            res <<= 1;
            if (c == '1')
                res |= 1;
        }
        return res;
    }
}

template <typename S, typename T>
istream &operator>>(istream &input, pair<S, T> &p)
{
    input >> p.first >> p.second;
    return input;
}

template <typename T>
istream &operator>>(istream &input, vector<T> &vec)
{
    for (auto &element : vec)
    {
        input >> element;
    }
    return input;
}