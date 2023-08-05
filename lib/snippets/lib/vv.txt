#include "common.h"
// Vector utilities
namespace vv {

// returns whether vec contains value
template <typename T, typename S>
inline bool contains(const vector<T>& vec, const S& value)
{
    // use two different typenames to allow for int value and vector<long long> vecs
    // (bad practice)
    auto it = std::find(vec.begin(), vec.end(), value);
    return (it != vec.end());
}

// returns index of element in a, returns -1 if element is not present
template <typename S, typename T>
inline int indexof(const vector<T>& a, const S& element)
{
    for (int i = 0; i < len(a); ++i) {
        if (a[i] == element) {
            return i;
        }
    }
    return -1;
}

// returns a range from [start, end) with an optional step
// behaves similarly to numpy arange
template <typename T>
inline vector<T> arange(T start, T end, T step)
{
    vector<T> result;
    for (T value = start; value < end; value += step) {
        result.pb(value);
    }
    return result;
}
template <typename T>
inline vector<T> arange(T start, T end)
{
    return arange(start, end, static_cast<T>(1));
}
template <typename T>
inline vector<T> arange(T end)
{
    return arange(static_cast<T>(0), end, static_cast<T>(1));
}

// returns a hashmap of <value, frequency> pairs
template <typename T>
inline unordered_map<T, ll, custom_hash> counter(const vector<T>& a, ll start, ll end)
{
    if (start < 0) {
        start += len(a);
    }
    if (end < 0) {
        end += len(a);
    }
    unordered_map<T, ll, custom_hash> result;
    rep(i, start, end)
    {
        result[a[i]]++;
    }

    return result;
}
// overload, [start, end of a]
template <typename T>
inline unordered_map<T, ll, custom_hash> counter(const vector<T>& a, ll start = 0)
{
    return counter(a, start, len(a));
}

// returns a sliced vector, a[start:end]
// behaves like python slicing (the slice is from [start, end))
template <typename T>
vector<T> slc(const vector<T>& a, int start, int end)
{
    if (start < 0) {
        start += len(a);
    }
    if (end < 0) {
        end += len(a);
    }
    return vector<T>(a.begin() + start, a.begin() + end);
}
template <typename T>
vector<T> slc(const vector<T>& a, int start = 0)
{
    return slc(a, start, len(a));
}

// returns a subvector of a, defined by the indices in idx
template <typename T, typename S>
vector<T> slc(const vector<T>& a, const vector<S> idx)
{
    int ll = len(idx);
    vector<T> result(ll);
    for (int i = 0; i < ll; i++) {
        result[i] = a[idx[i]];
    }
    return result;
}

template <typename T>
bool all(const vector<T>& a)
{
    return std::all_of(a.begin(), a.end(), [](bool b) { return b; });
}

template <typename T>
bool any(const vector<T>& a)
{
    return std::any_of(a.begin(), a.end(), [](bool b) { return b; });
}

// sums all the elements of a from [start, end)
template <typename T>
T sum(const vector<T>& a, int start, int end)
{
    if (start < 0) {
        start += len(a);
    }
    if (end < 0) {
        end += len(a);
    }
    return std::accumulate(a.begin(), a.begin() + end, T(0));
}
template <typename T>
T sum(const vector<T>& a, int start = 0)
{
    return sum(a, start, len(a));
}

// multiplies all the elements of a from [start, end)
template <typename T>
T product(const vector<T>& a, int start, int end, ll mm)
{
    if (start < 0) {
        start += len(a);
    }
    if (end < 0) {
        end += len(a);
    }
    T p(1);
    rep(i, start, end)
    {
        p *= a[i];
        if (mm > 0) {
            p %= mm;
        }
    }
    return p;
}
template <typename T>
T product(const vector<T>& a, int start = 0, ll mm = -1)
{
    return product(a, start, len(a), mm);
}

// returns min of a[start:end]
template <typename T>
T min(const vector<T>& a, int start, int end)
{
    if (start < 0) {
        start += len(a);
    }
    if (end < 0) {
        end += len(a);
    }

    T ans = a[start];
    rep(i, start + 1, end)
    {
        ans = std::min(ans, a[i]);
    }
    return ans;
}
template <typename T>
T min(const vector<T>& a, int start = 0)
{
    return min(a, start, len(a));
}

// returns max element of a[start:end]
template <typename T>
T max(const vector<T>& a, int start, int end)
{
    if (start < 0) {
        start += len(a);
    }
    if (end < 0) {
        end += len(a);
    }

    T ans = a[start];
    rep(i, start + 1, end)
    {
        ans = std::max(ans, a[i]);
    }
    return ans;
}
template <typename T>
T max(const vector<T>& a, int start = 0)
{
    return max(a, start, len(a));
}

// sorts a[start:end]
template <typename T, typename KeyFunc = Identity<T>>
void sort(vector<T>& a, int start, int end, KeyFunc keyFunc = Identity<T> {})
{
    if (start < 0) {
        start += len(a);
    }
    if (end < 0) {
        end += len(a);
    }
    if (start >= end || end > len(a)) {
        return; // Invalid indices or empty range
    }

    std::stable_sort(a.begin() + start, a.begin() + end,
        [&keyFunc](const T& x, const T& y) {
            return keyFunc(x) < keyFunc(y);
        });
}
template <typename T, typename KeyFunc = Identity<T>>
void sort(vector<T>& a, int start = 0, KeyFunc keyFunc = Identity<T> {})
{
    return sort(a, start, len(a), keyFunc);
}

// returns an array of indices of the sorting of a
// eg. if a is [1,6,3,2], then argsort returns [0,3,2,1]
template <typename T>
vector<int> argsort(const vector<T>& a)
{
    // Initialize original index positions
    vector<int> indices(a.size());
    for (int i = 0; i < len(indices); ++i) {
        indices[i] = i;
    }

    // Sort the indices based on comparing array values
    std::stable_sort(indices.begin(), indices.end(), [&](int i1, int i2) { return a[i1] < a[i2]; });

    return indices;
}

// returns the index of the maximum element
// if earliest is true, then return the earliest maximum element when there is a tie.
template <typename T>
int argmax(const vector<T>& a, ll start, ll end, bool earliest = true)
{
    if (start < 0) {
        start += len(a);
    }
    if (end < 0) {
        end += len(a);
    }
    T best = a[start];
    int best_idx = start;
    rep(i, start, end)
    {
        if (earliest ? a[i] > best : a[i] >= best) {
            best_idx = i;
            best = a[i];
        }
    }
    return best_idx;
}
template <typename T>
int argmax(const vector<T>& a, ll start, bool earliest = true)
{
    return argmax(a, start, len(a), earliest);
}
template <typename T>
int argmax(const vector<T>& a, bool earliest = true)
{
    return argmax(a, 0, len(a), earliest);
}

// returns the index of the smallest element
// if earliest is true, then return the earliest smallest element when there is a tie.
template <typename T>
int argmin(const vector<T>& a, ll start, ll end, bool earliest = true)
{
    if (start < 0) {
        start += len(a);
    }
    if (end < 0) {
        end += len(a);
    }
    T best = a[start];
    int best_idx = start;
    rep(i, start, end)
    {
        if (earliest ? a[i] < best : a[i] <= best) {
            best_idx = i;
            best = a[i];
        }
    }
    return best_idx;
}
template <typename T>
int argmin(const vector<T>& a, ll start, bool earliest = true)
{
    return argmin(a, start, len(a), earliest);
}
template <typename T>
int argmin(const vector<T>& a, bool earliest = true)
{
    return argmin(a, 0, len(a), earliest);
}

// fills vector a with value elem
template <typename S, typename T>
void fill(vector<T>& a, S elem)
{
    rep(i, 0, len(a))
    {
        a[i] = elem;
    }
}

// returns a vector ret s.t.
// ret[i] = sum(a[0:i])
template <typename T>
vector<T> cumsum(const vector<T>& a)
{
    vector<T> ret(a);
    rep(i, 1, len(a))
    {
        ret[i] += ret[i - 1];
    }
    return ret;
}

// returns a vector ret s.t.
// ret[i] = max(a[0:i]) if reverse is false
// ret[i] = max(a[i:]) if reverse is true
template <typename T>
vector<T> cummax(const vector<T>& a, bool reverse = false)
{
    vector<T> ret(a);
    ll n = len(a);
    if (reverse) {
        dep(i, n - 2, 0)
        {
            ret[i] = std::max(ret[i + 1], ret[i]);
        }
    } else {
        rep(i, 1, n)
        {
            ret[i] = std::max(ret[i], ret[i - 1]);
        }
    }
    return ret;
}

// returns a vector ret s.t.
// ret[i] = min(a[0:i]) if reverse is false
// ret[i] = min(a[i:]) if reverse is true
template <typename T>
vector<T> cummin(const vector<T>& a, bool reverse = false)
{
    vector<T> ret(a);
    ll n = len(a);
    if (reverse) {
        dep(i, n - 2, 0)
        {
            ret[i] = std::min(ret[i + 1], ret[i]);
        }
    } else {
        rep(i, 1, n)
        {
            ret[i] = std::min(ret[i], ret[i - 1]);
        }
    }
    return ret;
}

template <typename T>
bool is_lex_less(const vector<T>& a, const vector<T>& perm)
{
    // Compare the permutations lexicographically
    return std::lexicographical_compare(a.begin(), a.end(), perm.begin(), perm.end());
}
};