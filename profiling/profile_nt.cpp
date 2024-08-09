// #include<lib/constants/mod998244353.h>
// #include<lib/macros.h>
// #include<lib/print.h>
// #include<lib/inp.h>
// #include<lib/common.h>
// #include<lib/vv/sum.h>
// #include<lib/vv/counter.h>
// #include<lib/vv/sort.h>
// #include<lib/nt.h>
// #include<lib/mem.h>
#define GLOBAL_MOD 998244353
#ifndef DEBUG // Don't optimize locally
#pragma GCC optimize("O3")
#endif

#include <bits/stdc++.h>
#include <cassert>
#include <cstdio>

using namespace std;

typedef long long ll;
// typedef __int128_t ll;

// important constant to set for some problems
#ifdef GLOBAL_MOD
    const ll MOD = GLOBAL_MOD;
#else
    // Set the default MOD to 0 so that for a problem
    // that actually uses MOD you get a clear division
    // by zero error to remind you to include
    // lib/constants/mod*
    const ll MOD = 0;
#endif

//  Definition of the macro.
// if x, y, z are ordered non-descendingly
#define ordered(x, y, z) ((x) <= (y) && (y) <= (z))

// updates lhs to be the minimum of lhs and rhs
template <typename T, typename S>
bool chkmin(T& lhs, S rhs)
{
    if (lhs > static_cast<T>(rhs)) {
        lhs = static_cast<T>(rhs);
        return true;
    } else {
        return false;
    }
}
// updates lhs to be the maximum of lhs and rhs
template <typename T, typename S>
bool chkmax(T& lhs, S rhs)
{
     if (lhs < static_cast<T>(rhs)) {
        lhs = static_cast<T>(rhs);
        return true;
    } else {
        return false;
    }
}

// Because unsigned sizes are absolutely stupid
// Got burned on 1841C
template <typename T>
inline ll len(const T& v)
{
    return ll(v.size());
}

#define to_str to_string
#define pb push_back
#define eb emplace_back
#define mp make_pair
#define ALL(x) (x).begin(), (x).end()
#define SLC(x, i1, i2) (x).begin() + i1, (x).begin() + i2 + 1

/**
 * Computes ceildiv, but handles negatives properly
*/
template <typename T, typename Y>
inline ll ceildiv(T x, Y y)
{
    if (y < 0) {
        return ceildiv(-x, -y);
    }
    if (x < 0) {
        return x / y;
    }
    return x / y + (x % y != 0);
}

/**
 * Computes floordiv, but handles negatives properly
*/
template <typename T, typename Y>
inline ll floordiv(T x, Y y)
{
    if (y < 0) {
        return floordiv(-x, -y);
    }
    if (x < 0) {
        return -ceildiv(-x, y);
    }
    return x / y;
}

// Looping macros
// The "rep/dep" family, where rep(L, R) is [L, R)
// but dep is [R, L].
#define rep(i, d, u) for (ll i = (d); i < (u); ++i)
#define dep(i, u, d) for (ll i = (u); i >= (d); --i)
#define irep(i, d, u) for (i = (d); i < (u); ++i)
#define idep(i, u, d) for (i = (u); i >= (d); --i)
#define srep(i, d, u, s) for (ll i = (d); i < (u); i += s)

// The "FOR/DOR" family, everything is endpoint inclusive
#define FOR(i, d, u) for (ll i = (d); i <= (u); ++i)
#define SFOR(i, d, u, s) for (ll i = (d); i <= (u); i += s)
#define IFOR(i, d, u) for (i = (d); i <= (u); ++i)
#define DOR dep
#define IDOR idep

#define cep(t) while (t--)
#define CEPEAT_CAT_(a, b) a##b
#define CEPEAT_CAT(a, b) CEPEAT_CAT_(a, b)
#define cepeat(t) rep(CEPEAT_CAT(CEPEAT_COPY, __COUNTER__), 0, t)

#define foreach(i, c) for (auto& i : c)
#define foreachp(k, v, c) for (auto& [k, v] : c)

// Loops over all submasks of mask m
#define foreach_subset(u, m) for (ll u=m; u >= 0; u = u == 0 ? -1 : (u - 1) & m)

// Looping through a container
#define walk(i, container) for (ll i = 0; i < len(container); ++i)
#define reverse_walk(i, container) for (ll i = len(container) - 1; i >= 0; --i)
#define iter_walk(i, container) for (auto i = container.begin(); i != container.end(); i++)
#define reverse_iter_walk(i, container) for (auto i = container.rbegin(); i != container.rend(); i++)

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
        return (do_hash(key.first) << 21) ^ do_hash(key.second);
    }

    size_t operator()(const string& s) const
    {
        uint64_t out = 0;
        for (int i = 0; i < len(s); i++) {
            out = out * 37 + s[i];
        }
        return do_hash(out);
    }

    template <typename T>
    size_t operator()(const vector<T>& vec) const
    {
        size_t seed = len(vec);
        for (auto& i : vec) {
            seed ^= (*this)(i) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        }
        return seed;
    }

    template <long unsigned int T>
    size_t operator()(const bitset<T>& b) const
    {
        return do_hash(to_string(b));
    }

    template <typename T, size_t N>
    size_t operator()(const array<T, N>& a) const {
        size_t seed = len(a);
        for (auto& i : a) {
            seed ^= (*this)(i) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        }
        return seed;
    }
};

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

/**
 * Generate a random number between a and b inclusive
 *
 * Ex: uid(4, 9);
*/
#define uid(a, b) uniform_int_distribution<ll>(a, b)(rng)

typedef vector<vector<int>> vvi;
typedef vector<int> vi;
typedef array<ll, 2> array2;
typedef array<ll, 3> array3;
typedef array<ll, 4> array4;

typedef vector<vector<ll>> vvl;
typedef vector<string> vstr;
typedef vector<vector<string>> vvstr;
typedef vector<char> vc;
typedef vector<ll> vl;
typedef vector<bool> vb;
typedef vector<vb> vvb;
typedef pair<ll, ll> pl;
typedef pair<int, int> pi;
typedef pair<int, int> pii;
typedef vector<vector<pl>> vvpl;
typedef vector<pl> vpl;
typedef vector<pi> vpi;
typedef vector<double> vd;
typedef vector<long double> vld;

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


template <typename T>
using maxheap = priority_queue<T, vector<T>, less<T>>;
template <typename T>
using minheap = priority_queue<T, vector<T>, greater<T>>;

/**
 * Allows addition of dicts. Merges and adds values when keys overlap.
*/
template <typename K, typename V>
umap<K, V> operator+(const umap<K, V>& lhs, const umap<K, V>& rhs)
{
    umap<K, V> result = lhs;

    for (const auto& pair : rhs) {
        result[pair.first] += pair.second;
    }

    return result;
}

/**
 * Extract value from a map without modification.
 *
 * Ex. map << 5
 * is equivalent to map[5], but it does not insert the 5 into the map
 * if it is not there
*/
template <typename Key, typename Value>
Value operator<<(const umap<Key, Value>& map, const Key& key)
{
    auto it = map.find(key);
    if (it != map.end()) {
        return it->second;
    }
    return Value {}; // Default-constructed value
}

template <typename Key, typename Value>
Value operator<<(const std::map<Key, Value>& map, const Key& key)
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

#define RC(expr, x, lo, hi) ({                                \
    ll x;                                                     \
    using RC_t = std::remove_reference<decltype(expr)>::type; \
    vector<RC_t> lcret;                                       \
    IFOR(x, lo, hi)                                           \
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

// The first 4 directions are the normal up down left right
// the next 4 are diagonal directions, if you need that too
int dx[8] = { 1, 0, -1, 0, 1, -1, -1, 1 };
int dy[8] = { 0, 1, 0, -1, 1, 1,  -1, -1 };



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

// Linear search
// Note that these are inclusive: [lo, hi]
#define first_st(x, cond, lo, hi) ({                     \
    ll _INTERNAL_start = (lo);                           \
    ll _INTERNAL_end = (hi);                             \
    ll x;                                                \
    for (x = _INTERNAL_start; x <= _INTERNAL_end; x++) { \
        if (cond)                                        \
            break;                                       \
    }                                                    \
    x;                                                   \
})

#define last_st(x, cond, hi, lo) ({                      \
    ll _INTERNAL_start = (lo);                           \
    ll _INTERNAL_end = (hi);                             \
    ll x;                                                \
    for (x = _INTERNAL_end; x >= _INTERNAL_start; x--) { \
        if (cond)                                        \
            break;                                       \
    }                                                    \
    x;                                                   \
})

// Existential/Universal linear search
#define exists_st(x, cond, lo, hi) ({                    \
    bool _INTERNAL_any_good = false;                     \
    ll _INTERNAL_start = (lo);                           \
    ll _INTERNAL_end = (hi);                             \
    ll x;                                                \
    for (x = _INTERNAL_start; x <= _INTERNAL_end; x++) { \
        _INTERNAL_any_good |= (cond);                    \
    }                                                    \
    _INTERNAL_any_good;                                  \
})

#define all_st(x, cond, lo, hi) ({                       \
    bool _INTERNAL_all_good = true;                      \
    ll _INTERNAL_start = (lo);                           \
    ll _INTERNAL_end = (hi);                             \
    ll x;                                                \
    for (x = _INTERNAL_start; x <= _INTERNAL_end; x++) { \
        _INTERNAL_all_good &= (cond);                    \
    }                                                    \
    _INTERNAL_all_good;                                  \
})

// Fixed iteration continuous binary search (largest_st)
#define largest_double_st(mid, cond, lo, hi, num_iterations) ({ \
    double BISEARCH_LO = (lo);                                   \
    double BISEARCH_HI = (hi);                                   \
    double mid;                                                  \
    cepeat((num_iterations))                                     \
    {                                                            \
        mid = (BISEARCH_LO + BISEARCH_HI) / 2.0;                 \
        if ((cond)) {                                            \
            BISEARCH_LO = mid;                                   \
        } else {                                                 \
            BISEARCH_HI = mid;                                   \
        }                                                        \
    }                                                            \
    mid;                                                         \
})
// Fixed iteration continuous binary search (smallest_st)
#define smallest_double_st(mid, cond, lo, hi, num_iterations) ({ \
    double BISEARCH_LO = (lo);                                   \
    double BISEARCH_HI = (hi);                                   \
    double mid;                                                  \
    cepeat((num_iterations))                                     \
    {                                                            \
        mid = (BISEARCH_LO + BISEARCH_HI) / 2.0;                 \
        if ((cond)) {                                            \
            BISEARCH_HI = mid;                                   \
        } else {                                                 \
            BISEARCH_LO = mid;                                   \
        }                                                        \
    }                                                            \
    mid;                                                         \
})
// does % but doesn't mess up negatives
//  mod(4, 5) == mod(-1, 5) == mod(-6, 5)
template <typename T=ll, typename S=ll>
T mod(T a, S p)
{
    if (p >= 0) {
        return (a % p + p) % p;
    }
    return a;
}

template <typename T=ll>
T mod(T a)
{
    return mod(a, MOD);
}
template <typename T=ll, typename S=ll>
void chkmod(T& a, S m = MOD)
{
    a = mod(a, m);
}

/**
 * Clipped multiplication (cmul)
 *
 * Returns a * b, unless a * b will overflow, in which case it
 * clips it between LLONG_MIN and LLONG_MAX
*/
ll cmul(ll a, ll b)
{
    if (b == 0)
        return 0;
    if (b > 0) {
        if (a >= LLONG_MAX / b) {
            return LLONG_MAX;
        } else if (a <= LLONG_MIN / b) {
            return LLONG_MIN;
        }
        return a * b;
    }
    // b is negative
    if (a <= LLONG_MAX / b) {
        return LLONG_MAX;
    } else if (a >= LLONG_MIN / b) {
        return LLONG_MIN;
    }
    return a * b;
}

#define ITERATE_BORDER(arr, i_var, j_var, expr) \
    ll i_var = 0; \
    ll j_var = 0; \
    IFOR(i_var, 0, len(arr) - 1) expr \
    j_var = len(arr[0]) - 1; \
    IFOR(i_var, 0, len(arr) - 1) expr \
    i_var = 0; \
    IFOR(j_var, 1, len(arr[0]) - 2) expr \
    i_var = len(arr) - 1; \
    IFOR(j_var, 1, len(arr[0]) - 2) expr


// Function to calculate (base^exponent) using repeated squaring
template <typename T1=ll, typename T2=ll>
typename std::enable_if<!std::is_same<T1, int>::value, T1>::type
power(T1 base, T2 exponent,
      function<T1(T1, T1)> mul=[](T1 x, T1 y) { return x * y; },
      function<T1()> e=[]() { return T1(1); })
{
    T1 result = e();

    while (exponent > 0) {
        // If the exponent is odd, multiply the result by base
        if (exponent & 1) {
            result = mul(result, base);
        }
        exponent >>= 1;
        if (exponent == 0) {
            break;
        }

        // Square the base and reduce the exponent by half
        base = mul(base, base);
    }

    return result;
}

template <typename T2=ll>
ll power(int base, T2 exponent,
         function<ll(ll, ll)> mul=[](ll x, ll y) { return x * y; },
         function<ll()> e=[]() { return 1LL; })
{
    return power<ll, T2>(ll(base), exponent, mul, e);
}

ll cpower(ll base, ll exponent) {
    return power<ll, ll>(base, exponent, cmul);
}

// Printing
void init()
{
    ios_base::sync_with_stdio(false), cin.tie(nullptr);
    cout << setprecision(16) << std::fixed;
}

// Declarations of operator<< to avoid circular dependencies
template <typename T, size_t N> std::ostream &operator<<(std::ostream& os, const array<T, N>& a);
template <typename T1, typename T2> std::ostream& operator<<(std::ostream& os, const std::pair<T1, T2>& p);
template <typename K, typename V> std::ostream &operator<<(std::ostream &os, const unordered_map<K, V, custom_hash> &mp);
template <typename K, typename V> std::ostream &operator<<(std::ostream &os, const map<K, V> &mp);
template <typename T> std::ostream &operator<<(std::ostream &os, const std::vector<T> &v);
template <typename T> std::ostream &operator<<(std::ostream &os, const std::deque<T> &v);
template <typename T> std::ostream &operator<<(std::ostream &os, const std::vector<std::vector<T>> &vv);
template <typename T> std::ostream &operator<<(std::ostream &os, const std::set<T> &s);
template <typename T> std::ostream &operator<<(std::ostream &os, const std::multiset<T> &s);
template <typename T> std::ostream &operator<<(std::ostream &os, const std::unordered_set<T, custom_hash> &s);
template <typename K, typename V> std::ostream &operator<<(std::ostream &os, const std::unordered_map<K, V> &mp);

// Actual definitions
template <typename T1, typename T2>
std::ostream& operator<<(std::ostream& os, const std::pair<T1, T2>& p)
{
#ifndef ONLINE_JUDGE
#ifdef DEBUG
    return os << "(" << p.first << ", " << p.second << ")";
#else
    return os << p.first << " " << p.second;
#endif
#else
    return os << p.first << " " << p.second;
#endif
}

template <typename K, typename V>
std::ostream &operator<<(std::ostream &os, const unordered_map<K, V, custom_hash> &mp)
{
    os << "{ ";
    for (const auto &p : mp)
    {
        os << p.first << ": " << p.second << ", ";
    }
    os << "}";
    return os;
}

template <typename K, typename V>
std::ostream &operator<<(std::ostream &os, const map<K, V> &mp)
{
    os << "{ ";
    for (const auto &p : mp)
    {
        os << p.first << ": " << p.second << ", ";
    }
    os << "}";
    return os;
}

template <typename T>
std::ostream &operator<<(std::ostream &os, const std::vector<T> &v)
{
    for (auto it = v.begin(); it != v.end(); ++it)
    {
        os << *it;
        if (it != v.end() - 1)
        {
            os << " ";
        }
    }
    return os;
}

template <typename T>
std::ostream &operator<<(std::ostream &os, const std::deque<T> &v)
{
    for (auto it = v.begin(); it != v.end(); ++it)
    {
        os << *it;
        if (it != v.end() - 1)
        {
            os << " ";
        }
    }
    return os;
}

template <typename T>
std::ostream &operator<<(std::ostream &os, const std::vector<std::vector<T>> &vv)
{
    walk(i, vv)
    {
#ifndef ONLINE_JUDGE
#ifdef DEBUG
        os << i << ": ";
#endif
#endif
        os << vv[i];
        if (i != len(vv) - 1)
        {
            os << '\n';
        }
    }
    return os;
}

template <typename T, size_t N>
std::ostream &operator<<(std::ostream& os, const array<T, N>& a) {
    os << "{";
    FOR(i, 0, (int) N - 1) {
        os << a[i];
        if (i < (int) N - 1) os << " ";
    }
    os << "}";
    return os;
}

template <typename T>
std::ostream &operator<<(std::ostream &os, const std::set<T> &s)
{
    os << "{ ";
    for (const auto &item : s)
    {
        os << item << " ";
    }
    os << "}";
    return os;
}

template <typename T>
std::ostream &operator<<(std::ostream &os, const std::multiset<T> &s)
{
    os << "{ ";
    for (const auto &item : s)
    {
        os << item << " ";
    }
    os << "}";
    return os;
}

template <typename T>
std::ostream &operator<<(std::ostream &os, const std::unordered_set<T, custom_hash> &s)
{
    os << "{ ";
    for (const auto &item : s)
    {
        os << item << " ";
    }
    os << "}";
    return os;
}

template <typename K, typename V>
std::ostream &operator<<(std::ostream &os, const std::unordered_map<K, V> &mp)
{
    os << "{ ";
    for (const auto &p : mp)
    {
        os << p.first << ": " << p.second << ", ";
    }
    os << "}";
    return os;
}

template <typename T>
void print(const T &t)
{
#ifdef INTERACTIVE
    std::cout << t << std::endl;
#else
#ifdef DEBUG
    std::cout << t << std::endl;
#else
    std::cout << t << "\n";
#endif
#endif
}

template <typename T, typename... Args>
void print(const T &t, const Args &...args)
{
    std::cout << t << " ";
    print(args...);
}

template <typename T>
void dprint(const T &t)
{
#ifndef ONLINE_JUDGE
#ifdef DEBUG
    std::cout << t << std::endl;
#endif
#endif
}

template <typename T, typename... Args>
void dprint(const T &t, const Args &...args)
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
#ifdef DEBUG
int recur_depth = 0;
#define dbg(x)                                                                                                 \
    {                                                                                                          \
        ++recur_depth;                                                                                         \
        auto x_ = x;                                                                                           \
        --recur_depth;                                                                                         \
        cout << string(recur_depth, '\t') << #x << " = " << x_ << endl; \
    }
#else
#define dbg(x)
#endif
#else
#define dbg(x)
#endif

#define SAY_YES { print("YES"); return; }
#define SAY_NO { print("NO"); return; }
#define SAY_Yes { print("Yes"); return; }
#define SAY_No { print("No"); return; }
#define SAY_NEG1 { print(-1); return; }

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

template<typename T>
istream& operator>>(istream& input, deque<T>& vec) {
    for (auto& element : vec) {
        input >> element;
    }
    return input;
}

template <typename T, size_t N>
istream& operator>>(istream& input, array<T, N>& arr) {
    for (size_t i = 0; i < N; i++) {
        input >> arr[i];
    }
    return input;
}

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

    template <typename T>
    void read1(vector<T>& v) {
        FOR(i, 1, len(v) - 1) {
            cin >> v[i];
        }
    }

    // forward means the input is parsed as
    // b[0], b[1], ..., b[n - 1]
    // backwards means the input is parsed as
    // b[n - 1], b[n - 2], ..., b[0]
    template <size_t N>
    void read_bitset(bitset<N>& b, int n, bool reverse=false) {
        char ch;
        if (!reverse) {
            FOR(i, 0, n - 1) {
                cin >> ch;
                b[i] = ch == '1';
            }
        }
        else {
            DOR(i, n - 1, 0) {
                cin >> ch;
                b[i] = ch == '1';
            }
        }
    }

    void read_tree(vvpl& graph, bool one_indexed=false) {
        ll n = len(graph) - one_indexed;
        FOR(i, 0, n - 2) {
            ll u, v; cin >> u >> v;
            if(!one_indexed) {
                u--; v--;
            }
            graph[u].pb({v, 1});
            graph[v].pb({u, 1});
        }
    }

    template<typename T>
    void read(T& t) {
        cin >> t;
    }

    template<typename T, typename... Args>
    void read(T& t, Args&... args) {
        cin >> t;
        read(args...);
    }
}
namespace vv {
template <typename T>
T sum(const vector<T>& a, int start = 0, int end = -1)
{
    if (end < 0) {
        end = len(a) + end;
    }
    if (start > end) return T(0);
    return std::accumulate(a.begin() + start, a.begin() + end + 1, T(0));
}
}

namespace vv {
template <typename T>
unordered_map<T, ll, custom_hash> counter(const vector<T>& a, ll start = 0, ll end = -1)
{
    if (start < 0) {
        start += len(a);
    }
    if (end < 0) {
        end += len(a);
    }

    unordered_map<T, ll, custom_hash> result;
    FOR(i, start, end)
    {
        result[a[i]]++;
    }

    return result;
}
}
namespace vv {

template <typename T>
struct Identity {
    constexpr const T& operator()(const T& value) const
    {
        return value;
    }
};


template <typename T, typename KeyFunc = Identity<T>>
void sort(vector<T>& a, int start = 0, int end = -1, KeyFunc keyFunc = Identity<T> {})
{
    if (end < 0) {
        end += len(a);
    }
    if (start >= end || end >= len(a)) {
        return; // Invalid indices or empty range
    }

    std::stable_sort(a.begin() + start, a.begin() + end + 1,
        [&keyFunc](const T& x, const T& y) {
            return keyFunc(x) < keyFunc(y);
        });
}

template <typename T, typename KeyFunc = Identity<T>>
void rsort(vector<T>& a, int start = 0, int end = -1, KeyFunc keyFunc = Identity<T> {})
{
    if (end < 0) {
        end += len(a);
    }
    if (start >= end || end >= len(a)) {
        return; // Invalid indices or empty range
    }

    std::stable_sort(a.begin() + start, a.begin() + end + 1,
        [&keyFunc](const T& x, const T& y) {
            return keyFunc(x) > keyFunc(y);
        });
}
}

namespace nt {
vl primes;
vl is_composite;
bool sieve_done = false;

void do_sieve(ll max_prime)
{
    is_composite.resize(max_prime + 1);
    FOR(d, 2, max_prime)
    {
        if (!is_composite[d]) {
            primes.push_back(d);

            int x = 2 * d;
            while (x <= max_prime) {
                is_composite[x] = d;
                x += d;
            }
        }
    }
    sieve_done = true;
}

bool is_prime(ll n)
{
    // Checks if n is prime
    if (n <= 1) {
        return false;
    }

    if (n < len(is_composite)) {
        return !is_composite[n];
    }

    ll p = *prev(primes.end());
    if (p * p < n) {
        throw out_of_range("Generate more primes please");
    }

    ll i = 0;
    while (primes[i] * primes[i] <= n) {
        if (n % primes[i] == 0) {
            return false;
        }
        i++;
    }
    return true;
}

template <typename T=ll, typename T2=ll>
T sum_digits(T n, T2 b)
{
    T sum(0);
    while (n > 0) {
        sum += n % b;
        n /= b;
    }
    return sum;
}

template <typename T = ll, typename T2 = ll>
std::vector<T2> get_digits(T n, T2 b, ll pad = -1) {
    std::vector<T2> ans;
    ans.reserve(std::max(pad, 30LL));

    if (b == 2 && std::is_same<T, ll>::value) {
        // Special case for base 2 and T as long long
        while (n > 0) {
            ans.push_back(T2(n & 1));  // Extract the least significant bit
            n >>= 1;  // Shift right by 1 to divide by 2
        }
    } else {
        // General case for any base
        while (n > 0) {
            ans.push_back(T2(n % b));
            n /= b;
        }
    }

    while (len(ans) < pad) {
        ans.push_back(T2(0));
    }

    return ans;
}

template <typename T=ll, typename T2=ll>
T digits_to_num(const vector<T2>& digs, T2 b)
{
    T s(0);
    DOR(i, len(digs) - 1, 0)
    {
        s *= b;
        s += digs[i];
    }
    return s;
}

/**
 * Computes pow() under a mod.
 *
 * Specficially, base^e (mod m)
*/
template <typename T1=ll, typename T2=ll, typename T3=ll>
typename std::enable_if<!std::is_same<T1, int>::value, T1>::type
pow(T1 base, T2 e, T3 m=MOD)
{
    base = mod(base, m);
    T1 result(1); // Assumes 1 is the identity element

    while (e > 0) {
        if (e & 1) result = (result * base) % m;
        e /= 2;
        if (e == 0) break;
        base = (base * base) % m;
    }
    return result;
}

// Specialization for ints, because they are special
template <typename T2=ll, typename T3=ll>
ll pow(int base, T2 e, T3 m=MOD) {
    return pow<ll, T2, T3>(ll(base), e, m);
}

template <typename T1=ll, typename T2=ll>
T2 get_digit(T1 n, T2 b, ll i) {
    if (b == 2) {
        return ((1LL << i) & n) > 0;
    }
    else {
        return (n / nt::pow(b, i, -1)) % b;
    }
}

template <typename T1=ll>
int get_bit(T1 n, ll i) {
    return ((1LL << i) & n) > 0;
}

template <typename T1=ll>
void set_bit(T1& n, ll i, ll b) {
    T1 c = (1LL << i) & n;
    n ^= c ^ (b << i);
}

template <typename T=ll>
T inv(T x, T y)
{
    T p = y;

    T ax = 1;
    T ay = 0;
    while (x > 0) {
        T q = y / x;
        tie(ax, ay) = make_tuple(ay - q * ax, ax);
        tie(x, y) = make_tuple(y % x, x);
    }

    return mod(ay, p);
}

template <typename T=ll>
T mdiv(T x, T y, T m = MOD)
{
    if (m < 0) {
        return x / y;
    }
    x = mod(x, m);
    y = mod(y, m);
    return mod(x * inv(y, m), m);
}

template <typename T=ll, typename S=ll>
ll v_p(T x, S p)
{
    ll res = 0;
    while (x % p == 0) {
        ++res;
        x /= p;
    }
    return res;
}

template <typename T, typename S>
T factorial(T x, S m = MOD)
{
    ll p = 1;
    FOR(i, 1, x)
    {
        p *= i;
        p = mod(p, m);
    }
    return p;
}

bool is_pow_of_2(ll n)
{
    return (n > 0) && ((n & (n - 1)) == 0);
}

// Computes the largest non-negative integer
// e such that b^e <= x
ll floor_log(ll x, ll b) {
    assert(b > 1);
    ll ans = 0;
    while (x >= b) {
        ans++; x /= b;
    }
    return ans;
}

// Computes the first 2^i st 2^i >= x / y,
// x and y must be positive
ll ratio_log2(ll x, ll y) {
    // 2^(-j) >= x / y
    // y >= 2^j * x
    if (x > y) {
        return first_st(i, cmul(1LL << i, y) >= x, 0, 31);
    }
    else {
        return -last_st(j, cmul((1LL << j), x) <= y, 31, 0);
    }
};

ll phi(ll n)
{
    ll result = n;
    if (!sieve_done) {
        throw out_of_range("Sieve not done, please run do_sieve");
    }

    for (ll prime : primes) {
        if (prime * prime > n)
            break;
        if (n % prime == 0) {
            while (n % prime == 0) {
                n /= prime;
            }
            result -= result / prime;
        }
    }

    if (n > 1) {
        result -= result / n;
    }

    return result;
}

// Returns all possible values of
// floor(n / k) from k = 1 to n.
// There are 2*sqrt(n) such values
vl floor_fractions(ll n) {
    vl ret;
    for (ll k = 1; k * k <= n; k++) {
        ret.pb(n / k);
        if (k != n / k) ret.pb(k);
    }
    sort(ALL(ret));
    return ret;
}

// Returns all possible values of
// ceil(n / k) from k = 1 to n.
// There are 2*sqrt(n) such values
vl ceil_fractions(ll n) {
    vl ret;
    for (ll k = 1; k * k <= n; k++) {
        ret.pb(ceildiv(n, k));
        if (k != ceildiv(n, k)) ret.pb(k);
    }
    sort(ALL(ret));
    return ret;
}

vl get_divisors(ll n) {
    vl divisors;
    for (ll d = 1; d * d <= n; d++) {
        if (n % d == 0) {
            divisors.pb(d);
            if (d * d != n)
                divisors.pb(n / d);
        }
    }
    sort(ALL(divisors));
    return divisors;
}

ll num_divisors(ll n)
{
    ll divisors = 1;

    for (ll prime : primes) {
        if (prime * prime > n)
            break;

        ll count = 0;
        while (n % prime == 0) {
            n /= prime;
            count++;
        }

        divisors *= (count + 1);
    }

    if (n > 1) {
        divisors *= 2;
    }

    return divisors;
}

ll sum_divisors(ll n)
{
    ll sum = 1;

    for (ll prime : primes) {
        if (prime * prime > n)
            break;

        if (n % prime == 0) {
            ll factorSum = 1;
            ll power = 1;
            while (n % prime == 0) {
                n /= prime;
                power *= prime;
                factorSum += power;
            }
            sum *= factorSum;
        }
    }

    if (n > 1) {
        sum *= (n + 1);
    }

    return sum;
}

umapll primeFactorization(ll n)
{
    umapll factors;

    for (ll prime : primes) {
        if (prime * prime > n)
            break;

        ll exponent = 0;
        while (n % prime == 0) {
            n /= prime;
            exponent++;
        }

        if (exponent > 0) {
            factors[prime] = exponent;
        }
    }

    if (n > 1) {
        factors[n] = 1;
    }

    return factors;
}
}

namespace combo {
using namespace nt;
vl factorial;
vl ifactorial; // Stores 1 / factorial
bool factorial_computed = false;
void precompute_fac(ll n, ll m = MOD)
{
    factorial.resize(n + 1);
    ifactorial.resize(n + 1);
    factorial[0] = 1;
    FOR(i, 1, n)
    {
        factorial[i] = mod(factorial[i - 1] * i, m);
    }
    // Stealing idea from ecnerwala
    ifactorial[n] = mdiv(ll(1), factorial[n], m);

    DOR(i, n - 1, 0) {
        ifactorial[i] = mod(ifactorial[i + 1] * (i + 1), m);
    }

    factorial_computed = true;
}

ll choose(ll n, ll k, ll m = MOD)
{
    if (k > n)
        return 0;
    if (k < 0) return 0;
    if (!factorial_computed) {
        throw out_of_range("Make sure to call combo::precompute_fac");
    }
    return mod(mod(factorial[n] * ifactorial[k], m) * ifactorial[n - k], m);
}
} // namespace combo

int parseLine(char* line){
    // This assumes that a digit will be found and the line ends in " Kb".
    int i = strlen(line);
    const char* p = line;
    while (*p <'0' || *p > '9') p++;
    line[i-3] = '\0';
    i = atoi(p);
    return i;
}

int mem_usage(){ //Note: this value is in KB!
    FILE* file = fopen("/proc/self/status", "r");
    int result = -1;
    char line[128];

    while (fgets(line, 128, file) != NULL){
        if (strncmp(line, "VmSize:", 7) == 0){
            result = parseLine(line);
            break;
        }
    }
    fclose(file);
    return result;
}

const auto beg_time = std::chrono::high_resolution_clock::now();
// https://stackoverflow.com/questions/47980498/accurate-c-c-clock-on-a-multi-core-processor-with-auto-overclock?noredirect=1&lq=1
// Returns in ms
double time_elapsed() {
	return chrono::duration<double>(std::chrono::high_resolution_clock::now() -
	                                beg_time)
	    .count() * 1000;
}

using namespace vv;

void solve() {
    ll n = 1'000'000;
    vl nums(n); FOR(i, 0, n - 1) nums[i] = 1'000'000'000 - i;
    ll x = 0;
    double start = time_elapsed();
    foreach(num, nums) {
        x += nt::get_digits(num, 2LL).back();
    }
    print(x);
    print("nt::get_digits(base 2)", time_elapsed() - start);

    start = time_elapsed();
    foreach(num, nums) {
        x += nt::get_digits(num, 3LL).back();
    }
    print(x);
    print("nt::get_digits(base 3)", time_elapsed() - start);



    start = time_elapsed();
    foreach(num, nums) {
        x += nt::sum_digits(num, 2LL);
    }
    print(x);
    print("nt::sum_digits()", time_elapsed() - start);

}

int main() {
    init();
    solve();
    return 0;
}