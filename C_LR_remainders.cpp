// #include<lib/inp.h>
// #include<lib/sparsetable.h>
// #include<lib/print.h>
// #include<lib/macros.h>
// #include<lib/common.h>
#ifndef DEBUG // Don't optimize locally
#pragma GCC optimize("O3")
#endif

#include <bits/stdc++.h>
// #include <iostream>
// #include <set>
// #include <unordered_map>
// #include <unordered_set>
// #include <vector>
// #include <algorithm>
// #include <utility>
// #include <random>
// #include <climits>
// #include <numeric>
// #include <map>
// #include <chrono>
// #include <iomanip>

#include <cassert>
#include <cstdio>

using namespace std;

//  Definition of the macro.
// ass (a, b, x, y) is equivalent to a = x; b = y;
#define ass(a, b, x, y) (tie(a, b) = make_tuple(x, y));
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

typedef long long ll;
// typedef __int128_t ll;

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
#define SLC(x, i1, i2) (x).begin() + i1, (x).begin() + i2

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

// Looping
#define repe(i, d, u) for (ll i = (d); i < (u); ++i)
#define repi(i, d, u) for (ll i = (d); i <= (u); ++i)
#define dep(i, u, d) for (ll i = (u); i >= (d); --i)
#define irepi(i, d, u) for (i = (d); i <= (u); ++i)
#define irepe(i, d, u) for (i = (d); i < (u); ++i)
#define idep(i, u, d) for (i = (u); i >= (d); --i)
#define srepi(i, d, u, s) for (ll i = (d); i <= (u); i += s)
#define srepe(i, d, u, s) for (ll i = (d); i < (u); i += s)

#define cep(t) while (t--)
#define CEPEAT_CAT_(a, b) a##b
#define CEPEAT_CAT(a, b) CEPEAT_CAT_(a, b)
#define cepeat(t) repe(CEPEAT_CAT(CEPEAT_COPY, __COUNTER__), 0, t)

#define foreach(i, c) for (auto& i : c)
#define foreachp(k, v, c) for (auto& [k, v] : c)

// Looping through a container
#define walk(i, container) for (ll i = 0; i < len(container); ++i)
#define reverse_walk(i, container) for (ll i = len(container) - 1; i >= 0; --i)
#define iter_walk(i, container) for (auto i = container.begin(); i != container.end(); i++)
#define reverse_iter_walk(i, container) for (auto i = container.rbegin(); i != container.rend(); i++)

#define rep repe
#define srep srepe
#define irep irepe

#define FOR repi
#define DOR dep
#define SFOR srepi
#define IFOR irepi
#define IDOR idep

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

template <typename K, typename V>
umap<K, V> operator+(const umap<K, V>& lhs, const umap<K, V>& rhs)
{
    umap<K, V> result = lhs;

    for (const auto& pair : rhs) {
        result[pair.first] += pair.second;
    }

    return result;
}

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
    if (p > 0) {
        return (a % p + p) % p;
    }
    return a;
}

// important constant to set for some problems
const ll MOD = 998244353LL;
// const ll MOD = 1000000007;

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

ll cmul(ll a, ll b)
{
    if (b == 0)
        return 0;
    if (b > 0) {
        if (a >= LONG_LONG_MAX / b) {
            return LONG_LONG_MAX;
        } else if (a <= LONG_LONG_MIN / b) {
            return LONG_LONG_MIN;
        }
        return a * b;
    }
    // b is negative
    if (a <= LONG_LONG_MAX / b) {
        return LONG_LONG_MAX;
    } else if (a >= LONG_LONG_MIN / b) {
        return LONG_LONG_MIN;
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
    cout << setprecision(9);
}

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
    FOR(i, 0, (int) N - 1) {
        cout << a[i];
        if (i < (int) N - 1) cout << " ";
    }
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

    void read_tree(vvpl& graph) {
        ll n = len(graph);
        FOR(i, 0, n - 2) {
            ll u, v; cin >> u >> v;
            u--; v--;
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

template <typename T>
struct SparseTable {
public:
    vector<vector<T>> table;
    vector<ll> logTable;
    function<T(T, T)> operation;

    SparseTable(const vector<T>& arr, function<T(T, T)> op)
    {
        ll n = arr.size();
        ll logn = log2(int(n)) + 1;

        table.resize(n, vector<T>(logn));
        logTable.resize(n + 1);
        operation = op;

        // Precompute logarithm values and array sizes
        for (int i = 2; i <= n; i++) {
            logTable[i] = logTable[i / 2] + 1;
        }

        // Initialize the first column of the table
        for (int i = 0; i < n; i++) {
            table[i][0] = arr[i];
        }

        // Compute the rest of the table using dynamic programming
        for (int j = 1; (1 << j) <= n; j++) {
            for (int i = 0; (i + (1 << j) - 1) < n; i++) {
                table[i][j] = operation(table[i][j - 1], table[i + (1 << (j - 1))][j - 1]);
            }
        }
    }

    ll query(int left, int right) const
    {
        ll k = logTable[right - left + 1];
        return operation(table[left][k], table[right - (1 << k) + 1][k]);
    }

    ll query_nonidempotent(int left, int right) const
    {
        // print("new query", left, right);
        ll ans;
        bool first_loop = true;
        while(left <= right) {
            // print("range:", left, right);
            ll k = logTable[right - left + 1];
            int v = table[left][k];
            if (first_loop) {
                first_loop = false;
                ans = v;
            } else {
                ans = operation(ans, v);
            }
            left += (1L << k);
        }
        return ans;
    }
};

template <typename T>
struct MinSparseTable : SparseTable<T> {
    MinSparseTable(const vector<T>& v) : SparseTable<T>(
        v, [](ll x, ll y) {return min(x, y);}
    )
    {}
};

template <typename T>
struct MaxSparseTable : SparseTable<T> {
    MaxSparseTable(const vector<T>& v) : SparseTable<T>(
        v, [](ll x, ll y) {return max(x, y);}
    )
    {}
};
using namespace std;
using namespace inp;

void solve();
int main() {
    int T;
    cin >> T;
    while(T--) solve();
}

void solve() {
    int n,m; read(n,m);
    vector<int> a(n); read(a);
    string cmds; read(cmds);

    auto f = [&](int x, int y) {
        return (x * y) % m;
    };

    foreach(x, a) x = x % m;
    SparseTable<int> st(a, f);

    int s=0,e=n-1;
    vl r;
    foreach(c, cmds) {
        r.push_back(st.query_nonidempotent(s, e));
        if (c == 'L') {
            s++;
        } else {
            e--;
        }
    }
    print(r);
}