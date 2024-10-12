// Link: https://open.kattis.com/problems/mengersponge

#include<lib/macros.h>
#include<lib/print.h>
#include<lib/inp.h>
#include<lib/common.h>
#include<lib/num_type/rational.h>

void solve()
{
    ll L;
    cin >> L;
    Rational<ll> x, y, z;
    ll xn, xd, yn, yd, zn, zd;
    cin >> xn >> xd >> yn >> yd >> zn >> zd;
    using vrl = vector<Rational<ll>>;
    x = { xn, xd };
    y = { yn, yd };
    z = { zn, zd };
    set<vector<Rational<ll>>> points;
    rep(i, 0, 3)
    {
        rep(j, 0, 3)
        {
            rep(k, 0, 3)
            {
                points.insert(vector<Rational<ll>> { { i, 3 }, { j, 3 }, { k, 3 } });
            }
        }
    }
    points.erase(vrl { { 1, 3 }, { 1, 3 }, { 1, 3 } });
    points.erase(vrl { { 2, 3 }, { 1, 3 }, { 1, 3 } });
    points.erase(vrl { { 1, 3 }, { 2, 3 }, { 1, 3 } });
    points.erase(vrl { { 1, 3 }, { 1, 3 }, { 2, 3 } });
    points.erase(vrl { { 0, 3 }, { 1, 3 }, { 1, 3 } });
    points.erase(vrl { { 1, 3 }, { 0, 3 }, { 1, 3 } });
    points.erase(vrl { { 1, 3 }, { 1, 3 }, { 0, 3 } });

    auto check = [&]() -> pair<bool, vector<Rational<ll>>> {
        foreach (point, points) {
            if (ordered(point[0], x, point[0] + Rational<ll>(1, 3)) && ordered(point[1], y, point[1] + Rational<ll>(1, 3)) && ordered(point[2], z, point[2] + Rational<ll>(1, 3))) {
                return { true, point };
            }
        }
        return { false, {} };
    };
    cepeat(L)
    {
        auto [res, point] = check();
        if (!res) {
            print(0);
            return;
        } else {
            x = x - point[0];
            y = y - point[1];
            z = z - point[2];
            x = x * 3;
            y = y * 3;
            z = z * 3;
        }
    }
    print(1);
}

int main()
{
    init();
    solve();
    return 0;
}