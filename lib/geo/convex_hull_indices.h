#pragma once
#include <lib/common.h>
#include <lib/geo/base/point.h>
#include <lib/vv/argsort.h>

namespace geo
{
    /**
     * Returns the indices of the points on the convex hull. Either one can
     * supply a list of pairs or a list of Point objects.
     *
     * :param mode: Can either be "full", "lower", or "upper"
     * :param inclusive: If three points are collinear, whether to include the redundant point
     */
    template <typename T>
    vector<int> convex_hull_indices(vector<pair<T, T>> &XY, string mode = "full",
                           bool inclusive = false)
    {
        assert(mode == "full" || mode == "lower" || mode == "upper");
        ll N = XY.size();
        if (N == 1)
            return {0};
        if (N == 2)
        {
            if (XY[0] < XY[1])
                return {0, 1};
            if (XY[1] < XY[0])
                return {1, 0};
            if (inclusive)
                return {0, 1};
            return {0};
        }
        vector<int> I = vv::argsort(XY);

        auto check = [&](ll i, ll j, ll k) -> bool
        {
            auto xi = XY[i].fi, yi = XY[i].se;
            auto xj = XY[j].fi, yj = XY[j].se;
            auto xk = XY[k].fi, yk = XY[k].se;
            auto dx1 = xj - xi, dy1 = yj - yi;
            auto dx2 = xk - xj, dy2 = yk - yj;
            T det = dx1 * dy2 - dy1 * dx2;
            return (inclusive ? det >= 0 : det > 0);
        };

        auto calc = [&]()
        {
            vector<int> P;
            for (auto &&k : I)
            {
                while (P.size() > 1)
                {
                    auto i = P[P.size() - 2];
                    auto j = P[P.size() - 1];
                    if (check(i, j, k))
                        break;
                    P.pop_back();
                }
                P.emplace_back(k);
            }
            return P;
        };

        vector<int> P;
        if (mode == "full" || mode == "lower")
        {
            vector<int> Q = calc();
            P.insert(P.end(), ALL(Q));
        }
        if (mode == "full" || mode == "upper")
        {
            if (!P.empty())
                P.pop_back();
            reverse(ALL(I));
            vector<int> Q = calc();
            P.insert(P.end(), ALL(Q));
        }
        if (mode == "upper")
            reverse(ALL(P));
        while (len(P) >= 2 && XY[P[0]] == XY[P.back()])
            P.pop_back();
        return P;
    }

    template <typename T>
    vector<int> convex_hull_indices(vector<Point<T>> &XY, string mode = "full",
                           bool inclusive = false)
    {
        assert(mode == "full" || mode == "lower" || mode == "upper");
        ll N = XY.size();
        if (N == 1)
            return {0};
        if (N == 2)
        {
            if (XY[0] < XY[1])
                return {0, 1};
            if (XY[1] < XY[0])
                return {1, 0};
            if (inclusive)
                return {0, 1};
            return {0};
        }
        vector<int> I = vv::argsort(XY);

        auto check = [&](ll i, ll j, ll k) -> bool
        {
            auto xi = XY[i].x, yi = XY[i].y;
            auto xj = XY[j].x, yj = XY[j].y;
            auto xk = XY[k].x, yk = XY[k].y;
            auto dx1 = xj - xi, dy1 = yj - yi;
            auto dx2 = xk - xj, dy2 = yk - yj;
            T det = dx1 * dy2 - dy1 * dx2;
            return (inclusive ? det >= 0 : det > 0);
        };

        auto calc = [&]()
        {
            vector<int> P;
            for (auto &&k : I)
            {
                while (P.size() > 1)
                {
                    auto i = P[P.size() - 2];
                    auto j = P[P.size() - 1];
                    if (check(i, j, k))
                        break;
                    P.pop_back();
                }
                P.emplace_back(k);
            }
            return P;
        };

        vector<int> P;
        if (mode == "full" || mode == "lower")
        {
            vector<int> Q = calc();
            P.insert(P.end(), ALL(Q));
        }
        if (mode == "full" || mode == "upper")
        {
            if (!P.empty())
                P.pop_back();
            reverse(ALL(I));
            vector<int> Q = calc();
            P.insert(P.end(), ALL(Q));
        }
        if (mode == "upper")
            reverse(ALL(P));
        while (len(P) >= 2 && XY[P[0]] == XY[P.back()])
            P.pop_back();
        return P;
    }

} // namespace geo