#include <bits/stdc++.h>

using namespace std;

//  Definition of the macro.
// ass (a, b, x, y) is equivalent to a = x; b = y;
#define ass(a, b, x, y) (tie(a, b) = make_tuple(x, y));
// if x, y, z are ordered non-descendingly
#define ordered(x, y, z) ((x) <= (y) && (y) <= (z))

// updates lhs to be the minimum of lhs and rhs
template <typename T, typename S>
void chkmin(T& lhs, S rhs)
{
    lhs = min(lhs, T(rhs));
}
// updates lhs to be the maximum of lhs and rhs
template <typename T, typename S>
void chkmax(T& lhs, S rhs)
{
    lhs = max(lhs, T(rhs));
}

// returns a signed value for the size of a container
template <typename T>
inline int len(const T& v)
{
    return int(v.size());
}

#define to_str to_string
#define pb push_back
#define mp make_pair
#define ALL(x) (x).begin(), (x).end()

typedef long long ll;

// Looping
#define rep(i, d, u) for (ll i = (d); i < (u); ++i)
#define dep(i, u, d) for (ll i = (u); i >= (d); --i)
#define irep(i, d, u) for (i = (d); i < (u); ++i)
#define idep(i, u, d) for (i = (u); i >= (d); --i)
#define srep(i, d, u, s) for (ll i = (d); i < (u); i += s)
#define cep(t) while (t--)
#define foreach(i, c) for (auto& i : c)
#define foreachp(k, v, c) for (auto& [k, v] : c)
// Looping through a container
#define walk(i, container) for (ll i = 0; i < len(container); ++i)
#define reverse_walk(i, container) for (ll i = len(container) - 1; i >= 0; --i)
#define iter_walk(i, container) for (auto i = container.begin(); i != container.end(); i++)

struct custom_hash {
    static uint64_t splitmix64(uint64_t x)
    {
        // http://xorshift.di.unimi.it/splitmix64.c
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }

    size_t do_hash(uint64_t x) const
    {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }

    size_t operator()(uint64_t x) const
    {
        return do_hash(x);
    }

    template <typename T1, typename T2>
    size_t operator()(const std::pair<T1, T2>& key) const
    {
        return (*this)(((*this)(key.first) * 37) ^ (*this)(key.second));
    }

    size_t operator()(string s) const
    {
        uint64_t out = 0;
        for (int i = 0; i < s.size(); i++) {
            out = out * 37 + s[i];
        }
        return do_hash(out);
    }
};

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

#define uid(a, b) uniform_int_distribution<ll>(a, b)(rng)

template <typename T>
struct Identity {
    constexpr const T& operator()(const T& value) const
    {
        return value;
    }
};

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

typedef vector<vector<int>> vvi;
typedef vector<int> vi;

typedef vector<vector<ll>> vvl;
typedef vector<vector<string>> vvs;
typedef vector<ll> vl;
typedef vector<bool> vb;
typedef pair<ll, ll> pl;
typedef vector<vector<pl>> vvpl;
typedef vector<pl> vpl;

// Maps
typedef unordered_map<ll, ll, custom_hash> umapll;
typedef unordered_map<ll, vl, custom_hash> umaplvl;
typedef unordered_map<string, ll, custom_hash> umapstrl;
typedef unordered_map<ll, string, custom_hash> umaplstr;

template <typename K, typename V>
using umap = unordered_map<K, V, custom_hash>;

typedef unordered_set<ll, custom_hash> usetl;
template <typename K>
using uset = unordered_set<K, custom_hash>;

umapll operator+(const umapll& lhs, const umapll& rhs)
{
    umapll result = lhs;

    for (const auto& pair : rhs) {
        result[pair.first] += pair.second;
    }

    return result;
}

template <typename Key, typename Value>
Value mget(const std::unordered_map<Key, Value, custom_hash>& map, const Key& key)
{
    auto it = map.find(key);
    if (it != map.end()) {
        return it->second;
    }
    return Value {}; // Default-constructed value
}

template <typename K, typename V>
void initmap(umap<K, V>& counts)
{
    counts.reserve(250000);
    counts.max_load_factor(0.25);
}

// List manipulation
typedef priority_queue<ll, vl, greater<ll>> minheap;
typedef priority_queue<ll, vl, less<ll>> maxheap;

#define RC(expr, x, lo, hi) ({                                \
    ll x;                                                     \
    using RC_t = std::remove_reference<decltype(expr)>::type; \
    vector<RC_t> lcret;                                       \
    irep(x, lo, hi)                                           \
    {                                                         \
        lcret.push_back(expr);                                \
    }                                                         \
    lcret;                                                    \
})

#define LC(expr, x, arr) ({                                               \
    using LCx_t = std::remove_reference<decltype(arr)>::type::value_type; \
    LCx_t x;                                                              \
    using LCexpr_t = std::remove_reference<decltype(expr)>::type;         \
    vector<LCexpr_t> lcret;                                               \
    foreach (LC_i, arr) {                                                 \
        x = LC_i; /*Using LC_i and then x = LC_i pacifies -Wshadow*/      \
        lcret.push_back(expr);                                            \
    }                                                                     \
    lcret;                                                                \
})

int dx[4] = { 1, 0, -1, 0 };
int dy[4] = { 0, 1, 0, -1 };

// Binary Search
// NOTE: lo and hi are inclusive;
// Eg. largest_st(x, a[x] < 5, 0, 10) will search for x between [0, 10]
#define largest_st(mid, cond, lo, hi) ({                          \
    ll BISEARCH_l = (lo), BISEARCH_r = (hi), BISEARCH_ans = (hi); \
    ll mid;                                                       \
    while (BISEARCH_l <= BISEARCH_r) {                            \
        mid = (BISEARCH_l + BISEARCH_r) / 2;                      \
        if ((cond)) {                                             \
            BISEARCH_ans = (mid);                                 \
            BISEARCH_l = (mid) + 1;                               \
        } else {                                                  \
            BISEARCH_r = (mid)-1;                                 \
        }                                                         \
    }                                                             \
    mid = BISEARCH_ans;                                           \
    if (!((cond))) {                                              \
        BISEARCH_ans = (lo)-1;                                    \
    }                                                             \
    BISEARCH_ans;                                                 \
})

#define smallest_st(mid, cond, lo, hi) ({                         \
    ll BISEARCH_l = (lo), BISEARCH_r = (hi), BISEARCH_ans = (hi); \
    ll mid;                                                       \
    while (BISEARCH_l <= BISEARCH_r) {                            \
        mid = (BISEARCH_l + BISEARCH_r) / 2;                      \
        if ((cond)) {                                             \
            BISEARCH_ans = (mid);                                 \
            BISEARCH_r = (mid)-1;                                 \
        } else {                                                  \
            BISEARCH_l = (mid) + 1;                               \
        }                                                         \
    }                                                             \
    mid = BISEARCH_ans;                                           \
    if (!((cond))) {                                              \
        BISEARCH_ans = (hi) + 1;                                  \
    }                                                             \
    BISEARCH_ans;                                                 \
})

// Strings
namespace str {
string lower(const string& s)
{
    string result = s;
    transform(result.begin(), result.end(), result.begin(), ::tolower);
    return result;
}

string upper(const string& s)
{
    string result = s;
    transform(result.begin(), result.end(), result.begin(), ::toupper);
    return result;
}

template <typename T>
string join(const vector<T>& elements, const string& delimiter)
{
    ostringstream oss;
    for (size_t i = 0; i < elements.size(); ++i) {
        if (i != 0) {
            oss << delimiter;
        }
        oss << elements[i];
    }
    return oss.str();
}

int stoi(char ch)
{
    return int(ch - '0');
}

string slc(const string& s, int start, int end)
{
    return s.substr(start, end - start);
}

vector<string> split(const string& s, char delimiter)
{
    vector<string> result;
    stringstream ss(s);
    string token;

    while (getline(ss, token, delimiter)) {
        result.push_back(token);
    }

    return result;
}

string fill(const string& s, int num)
{
    string ret = "";
    for (int i = 0; i < num; i++) {
        ret += s;
    }
    return ret;
}
}

namespace mset {
template <typename S, typename T>
void mset_del(S& ss, T x)
{
    auto it = ss.find(x);
    if (it == ss.end()) {
        throw std::out_of_range("element not found");
    }
    ss.erase(it);
}

template <typename S, typename T>
void mset_move(S& ss1, S& ss2, T x)
{
    auto ptr = ss1.find(x);
    if (ptr != ss1.end()) {
        ss1.erase(ptr);
        ss2.insert(x);
    } else {
        throw std::out_of_range("element not found");
    }
}

template <typename T>
T min(multiset<T>& ss)
{
    if (ss.empty()) {
        throw out_of_range("Empty set min");
    }
    return *(ss.begin());
}

template <typename T>
T max(multiset<T>& ss)
{
    if (ss.empty()) {
        throw out_of_range("Empty set max");
    }
    return *(ss.rbegin());
}

template <typename T>
T min(set<T>& ss)
{
    if (ss.empty()) {
        throw out_of_range("Empty set min");
    }
    return *(ss.begin());
}

template <typename T>
T max(set<T>& ss)
{
    if (ss.empty()) {
        throw out_of_range("Empty set max");
    }
    return *(ss.rbegin());
}

template <typename T, typename V>
T min(map<T, V>& ss)
{
    if (ss.empty()) {
        throw out_of_range("Empty set min");
    }
    return (ss.begin())->first;
}

template <typename T, typename V>
T max(map<T, V>& ss)
{
    if (ss.empty()) {
        throw out_of_range("Empty set max");
    }
    return (ss.rbegin())->first;
}
}

typedef multiset<ll> msetl;

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

// Printing

void init()
{
    ios_base::sync_with_stdio(false), cin.tie(nullptr);
}

template <typename T>
void print(const T& t)
{
#ifdef INTERACTIVE
    std::cout << t << std::endl;
#else
    std::cout << t << "\n";
#endif
}

template <typename T, typename... Args>
void print(const T& t, const Args&... args)
{
    std::cout << t << " ";
    print(args...);
}

template <typename T>
void dprint(const T& t)
{
#ifndef ONLINE_JUDGE
#ifdef DEBUG
    std::cout << t << std::endl;
#endif
#endif
}

template <typename T, typename... Args>
void dprint(const T& t, const Args&... args)
{
#ifndef ONLINE_JUDGE
#ifdef DEBUG
    std::cout << t << " ";
    print(args...);
#endif
#endif
}

// Fancy variable debugging, stolen from:
// https://codeforces.com/blog/entry/79024
#ifndef ONLINE_JUDGE
int recur_depth = 0;
#define dbg(x)                                                                                                 \
    {                                                                                                          \
        ++recur_depth;                                                                                         \
        auto x_ = x;                                                                                           \
        --recur_depth;                                                                                         \
        cout << string(recur_depth, '\t') << __func__ << ":" << __LINE__ << "\t" << #x << " = " << x_ << endl; \
    }
#else
#define dbg(x)
#endif

template <typename K, typename V>
std::ostream& operator<<(std::ostream& os, const unordered_map<K, V, custom_hash>& mp)
{
    os << "{ ";
    for (const auto& p : mp) {
        os << p.first << ": " << p.second << ", ";
    }
    os << "}";
    return os;
}

template <typename K, typename V>
std::ostream& operator<<(std::ostream& os, const map<K, V>& mp)
{
    os << "{ ";
    for (const auto& p : mp) {
        os << p.first << ": " << p.second << ", ";
    }
    os << "}";
    return os;
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& v)
{
    for (auto it = v.begin(); it != v.end(); ++it) {
        os << *it;
        if (it != v.end() - 1) {
            os << " ";
        }
    }
    return os;
}

template <typename T1, typename T2>
std::ostream& operator<<(std::ostream& os, const std::pair<T1, T2>& p)
{
    os << "(" << p.first << ", " << p.second << ")";
    return os;
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const std::set<T>& s)
{
    os << "{ ";
    for (const auto& item : s) {
        os << item << " ";
    }
    os << "}";
    return os;
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const std::multiset<T>& s)
{
    os << "{ ";
    for (const auto& item : s) {
        os << item << " ";
    }
    os << "}";
    return os;
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const std::unordered_set<T, custom_hash>& s)
{
    os << "{ ";
    for (const auto& item : s) {
        os << item << " ";
    }
    os << "}";
    return os;
}

template <typename K, typename V>
std::ostream& operator<<(std::ostream& os, const std::unordered_map<K, V>& mp)
{
    os << "{ ";
    for (const auto& p : mp) {
        os << p.first << ": " << p.second << ", ";
    }
    os << "}";
    return os;
}

template <typename T>
istream& operator>>(istream& input, vector<T>& vec)
{
    for (auto& element : vec) {
        input >> element;
    }
    return input;
}