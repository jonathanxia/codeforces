#include <lib/common.h>

// CUM(ULATIVE)

namespace cum {

// Note that all queries are inclusive
template <typename T = ll>
struct cum {
    using cumfunc_t = function<T(T, T)>;

    vector<T> cum_data;
    vector<T> rcum_data;
    ll n;
    // The operation to perform cumulatively
    cumfunc_t op;
    // The inverse operation used for subarray queries
    cumfunc_t inv;
    T identity;

    cum(vector<T> raw_data, cumfunc_t operation, cumfunc_t inverse, T _identity = 0)
        : cum_data(raw_data)
        , rcum_data(raw_data)
        , n { len(raw_data) }
        , op(operation)
        , inv(inverse)
        , identity { _identity }
    {
        repe(i, 1, n)
            cum_data[i] = op(cum_data[i], cum_data[i - 1]);
        dep(i, n - 2, 0)
            rcum_data[i] = op(rcum_data[i], rcum_data[i + 1]);
    }

    T prefix(ll idx) const
    {
        if (idx < 0)
            return identity;
        if (idx >= n)
            return cum_data.back();
        return cum_data[idx];
    }

    T suffix(ll idx) const
    {
        if (idx >= n)
            return identity;
        if (idx < 0)
            return rcum_data[0];
        return rcum_data[idx];
    }

    T query(ll idx1, ll idx2) const
    {
        if (idx1 <= 0)
            return prefix(idx2);
        if (idx2 >= n)
            idx2 = n - 1;
        return inv(cum_data[idx2], cum_data[idx1 - 1]);
    }
};

template <typename T = ll>
class sum : public cum<T> {
public:
    sum(vector<T> raw_data)
        : cum<T>(
            raw_data, [](T a, T b) { return a + b; }, [](T a, T b) { return a - b; }, T(0))
    {
    }
};

template <typename T = ll>
class prod : public cum<T> {
public:
    prod(vector<T> raw_data)
        : cum<T>(
            raw_data, [](T a, T b) { return a * b; }, [](T a, T b) { return a / b; }, T(1))
    {
    }
};

// c++ has overloaded the "xor" token, so we must use "XOR" instead
template <typename T = ll>
class XOR : public cum<T> {
public:
    XOR(vector<T> raw_data)
        : cum<T>(
            raw_data, [](T a, T b) { return a ^ b; }, [](T a, T b) { return a ^ b; }, T(0))
    {
    }
};

template <typename T = ll>
class min : public cum<T> {
public:
    min(vector<T> raw_data)
        : cum<T>(
            raw_data, [](T a, T b) { return ::min(a, b); }, [](T a, T b) { return numeric_limits<T>::max(); }, numeric_limits<T>::max())
    {
    }
};

template <typename T = ll>
class max : public cum<T> {
public:
    max(vector<T> raw_data)
        : cum<T>(
            raw_data, [](T a, T b) { return ::max(a, b); }, [](T a, T b) { return numeric_limits<T>::min(); }, numeric_limits<T>::min())
    {
    }
};

typedef cum<ll> ming;
}