#pragma once
#include <lib/common.h>
#include <lib/vv/slc.h>
#include <lib/vv/argsort.h>

template <typename S, typename T>
struct DiscretePiecewiseConstant {
    vector<S> x;
    vector<T> y;
    vector<T> integral;
    ll n;
    /**
     * points_: each of the points (a, b) means f(x) = y for x >= a
    */
    DiscretePiecewiseConstant(const vector<pair<S, T>>& points_)
    {
        n = len(points_);
        x.resize(n);
        y.resize(n);
        FOR(i, 0, n - 1) {
            x[i] = points_[i].first;
            y[i] = points_[i].second;
        }
        auto s_idx = vv::argsort(x);
        x = vv::slc(x, s_idx);
        y = vv::slc(y, s_idx);

        integral.resize(n, 0);
        integral[0] = y[0];
        FOR(i, 1, n - 1) {
            integral[i] = integral[i - 1];
            // From x[i - 1] + 1 to x[i] - 1
            integral[i] += (x[i] - x[i - 1] - 1) * y[i - 1];
            integral[i] += y[i];
        }
    }

    T operator()(const S& x_) {
        ll i = largest_st(t, x[t] <= x_, 0, n - 1);
        if (i < 0) return T(0);

        return y[i];
    }

    // Sum of function up to and including t
    T prefix_sum(const S& t) {
        // Integrate up to t
        ll i = largest_st(j, x[j] <= t, 0, n - 1);
        if (i < 0) return T(0);
        T ans = integral[i];

        // from x[i] + 1 to t, inclusive
        return ans + (t - x[i]) * y[i];
    }

    // Sum of the function from t1 to t2, inclusive
    T sum(const S& t1, const S& t2) {
        return prefix_sum(t2) - prefix_sum(t1 - 1);
    }
};

