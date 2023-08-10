#include <lib/common.h>

template <typename T>
struct Identity {
    constexpr const T& operator()(const T& value) const {
        return value;
    }
};

// Personal vectors
namespace vv {
    template <typename T>
    bool contains(const vector<T>& vec, const T& value) {
        auto it = std::find(vec.begin(), vec.end(), value);
        return (it != vec.end());
    }

    template <typename S, typename T>
    int indexof(const vector<T>& a, const S& element) {
        for (int i = 0; i < len(a); ++i) {
            if (a[i] == element) {
                return i;
            }
        }
        return -1;
    }

    template <typename T>
    inline vector<T> arange(T start, T end, T step = 1) {
        vector<T> result;
        for (T value = start; value <= end; value += step) {
            result.pb(value);
        }
        return result;
    }

    template <typename T>
    unordered_map<T, ll, custom_hash> counter(const vector<T>& a, ll start=0, ll end=-1) {
        if (end == -1) {
            end = len(a) - 1;
        }
        unordered_map<T, ll, custom_hash> result;
        rep(i, start, end) {
            result[a[i]]++;
        }

        return result;
    }

    template <typename T>
    vector<T> slc(const vector<T>& a, int start=0, int end=-1) {
        int n = len(a);
        if (end == -1) {
            end = n - 1;
        }
        int length = end - start + 1;
        vector<T> result(length);
        for (int i = 0; i < length; i++) {
            result[i] = a[start + i];
        }
        return result;
    }

    template <typename T, typename S>
    vector<T> slc(const vector<T>& a, const vector<S> idx) {
        int ll = len(idx);
        vector<T> result(ll);
        for (int i = 0; i < ll; i++) {
            result[i] = a[idx[i]];
        }
        return result;
    }

    template <typename T>
    bool all(const vector<T>& a) {
        return std::all_of(a.begin(), a.end(), [](bool b){ return b; });
    }

    template <typename T>
    bool any(const vector<T>& a) {
        return std::any_of(a.begin(), a.end(), [](bool b){ return b; });
    }

    template <typename T>
    T sum(const vector<T>& a, int start=0, int end=-1) {
        if (end < 0) {
            end = len(a) + end;
        }
        return std::accumulate(a.begin(), a.begin() + end + 1, T(0));
    }

    template <typename T>
    T prod(const vector<T>& a, int start=0, int end=-1, ll mm = -1) {
        if (end < 0) {
            end = len(a) + end;
        }
        T p(1);
        rep(i, start, end) {
            p = p * a[i];
            if (mm > 0) {
                p %= mm;
            }
        }
        return p;
    }

    template <typename T>
    T min(const vector<T>& a, int start=0, int end=-1) {
        if (end == -1) {
            end = len(a) - 1;
        }

        T ans = a[start];
        rep(i, start + 1, end) {
            ans = std::min(ans, a[i]);
        }
        return ans;
    }

    template <typename T>
    T max(const vector<T>& a, int start=0, int end=-1) {
        if (end == -1) {
            end = len(a) - 1;
        }

        T ans = a[start];
        rep(i, start + 1, end) {
            ans = std::max(ans, a[i]);
        }
        return ans;
    }

    template <typename T, typename KeyFunc = Identity<T>>
    void sort(vector<T>& a, int start = 0, int end = -1, KeyFunc keyFunc = Identity<T>{}) {
        if (end == -1) {
            end = len(a) - 1;
        }
        if (start >= end || end >= len(a)) {
            return;  // Invalid indices or empty range
        }

        std::stable_sort(a.begin() + start, a.begin() + end + 1,
                [&keyFunc](const T& x, const T& y) {
                    return keyFunc(x) < keyFunc(y);
                });
    }

    template <typename T>
    vector<int> argsort(const vector<T>& a) {
        // Initialize original index positions
        vector<int> indices(a.size());
        for (int i = 0; i < len(indices); ++i) {
            indices[i] = i;
        }

        // Sort the indices based on comparing array values
        std::stable_sort(indices.begin(), indices.end(), [&](int i1, int i2)
                         { return a[i1] < a[i2]; });

        return indices;
    }

    template <typename T>
    int argmax(const vector<T>& a, ll start=0, ll end=-1) {
        if (end == -1) {
            end = len(a) - 1;
        }
        T best = a[start];
        int best_idx = start;
        rep(i, start, end) {
            if (a[i] > best) {
                best_idx = i;
                best = a[i];
            }
        }
        return best_idx;
    }

    template <typename T>
    int argmin(const vector<T>& a, ll start=0, ll end=-1) {
        T best = a[start];
        int best_idx = start;
        if (end == -1) {
            end = len(a) - 1;
        }
        rep(i, start, end) {
            if (a[i] < best) {
                best_idx = i;
                best = a[i];
            }
        }
        return best_idx;
    }

    template <typename S, typename T>
    void fill(vector<T>& a, S elem) {
        rep(i, 0, len(a) - 1) {
            a[i] = elem;
        }
    }

    template <typename T>
    vector<T> cumsum(const vector<T>& a) {
        vector<T> ret(a);
        rep(i, 1, len(a) - 1) {
            ret[i] += ret[i - 1];
        }
        return ret;
    }

    template <typename T>
    vector<T> cummax(const vector<T>& a, bool reverse=false) {
        vector<T> ret(a);
        ll n = len(a);
        if (reverse) {
            dep(i, n - 2, 0) {
                ret[i] = std::max(ret[i + 1], ret[i]);
            }
        }
        else {
            rep(i, 1, n - 1)
            {
                ret[i] = std::max(ret[i], ret[i - 1]);
            }
        }
        return ret;
    }

    template <typename T>
    vector<T> cummin(const vector<T>& a, bool reverse=false) {
        vector<T> ret(a);
        ll n = len(a);
        if (reverse) {
            dep(i, n - 2, 0) {
                ret[i] = std::min(ret[i + 1], ret[i]);
            }
        }
        else {
            rep(i, 1, n - 1)
            {
                ret[i] = std::min(ret[i], ret[i - 1]);
            }
        }
        return ret;
    }

    template <typename T>
    bool is_lex_less(const vector<T>& a, const vector<T>& perm) {
        // Compare the permutations lexicographically
        return std::lexicographical_compare(a.begin(), a.end(), perm.begin(), perm.end());
    }

    template <typename T>
    vector<pair<T, ll>> with_idx(const vector<T>& a) {
        vector<pair<T, ll>> out;
        ll n = len(a);
        rep(i, 0, n - 1) {
            out.pb(mp(a[i], i));
        }
        return out;
    }
};

using namespace vv;