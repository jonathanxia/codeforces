// #include<lib/common.h>
// #include<lib/vv.h>
// #include<lib/nt.h>
#ifndef DEBUG // Don't optimize locally
#pragma GCC optimize("O3")
#endif

#include <bits/stdc++.h>
#include <cassert>
#include <cstdio>

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

using namespace std;

#define ass(a, b, x, y) (tie(a, b) = make_tuple(x, y));
#define ordered(x, y, z) ((x) <= (y) && (y) <= (z))
#define FNCT function

template <typename T, typename S>
void chkmin(T& lhs, S rhs) {
	lhs = min(lhs, T(rhs));
}
template <typename T, typename S>
void chkmax(T& lhs, S rhs) {
	lhs = max(lhs, T(rhs));
}

typedef long long ll;
// typedef __int128_t ll;

// Because unsigned sizes are absolutely stupid
// Got burned on 1841C
template <typename T>
inline ll len(const T& v) {
    return ll(v.size());
}

#define to_str to_string
#define pb push_back
#define eb emplace_back
#define mp make_pair
#define ALL(x) (x).begin(), (x).end()
#define SLC(x, i1, i2) (x).begin() + i1, (x).begin() + i2


// Looping
#define rep(i, d, u) for(ll i = (d); i <= (u); ++i)
#define rep0(i, u) for(ll i = 0; i <= (u); ++i)
#define dep(i, u, d) for(ll i = (u); i >= (d); --i)
#define dep0(i, u) for(ll i = (u); i >= 0; --i)
#define irep(i, d, u) for(i = (d); i <= (u); ++i)
#define idep(i, u, d) for(i = (u); i >= (d); --i)
#define srep(i, d, u, s) for(ll i = (d); i <= (u); i += s)
#define sdep(i, d, u, s) for(ll i = (d); i >= (u); i -= s)
#define cep(t) while(t--)
#define foreach(i, c) for(auto& i : c)
#define foreachp(k, v, c) for (auto& [k, v] : c)

template<typename T>
using ordered_set = tree<
    T,
    null_type,
    less<T>,
    rb_tree_tag,
    tree_order_statistics_node_update>;
// find_by_order, order_of_key


struct custom_hash {
    static uint64_t splitmix64(uint64_t x) {
        // http://xorshift.di.unimi.it/splitmix64.c
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }

    size_t do_hash(uint64_t x) const {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }

    size_t operator()(uint64_t x) const {
        return do_hash(x);
    }

    template <typename T1, typename T2>
    size_t operator()(const std::pair<T1, T2>& key) const {
        return (*this)(((*this)(key.first) * 37) ^ (*this)(key.second));
    }

    size_t operator()(string s) const {
        uint64_t out = 0;
        for (int i = 0; i < (int) (s.size()); i++) {
            out = out * 37 + s[i];
        }
        return do_hash(out);
    }
};

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
#define uid(a, b) uniform_int_distribution<ll>(a, b)(rng)

typedef vector<vector<int>> vvi;
typedef vector<int> vi;
typedef vector<string> vs;
typedef array<ll, 2> array2;
typedef array<ll, 3> array3;
typedef array<ll, 4> array4;

typedef vector<vector<ll>> vvl;
typedef vector<vector<string>> vvs;
typedef vector<ll> vl;
typedef vector<bool> vb;
typedef pair<ll, ll> pl;
typedef pair<int, int> pi;
typedef vector<vector<pl>> vvpl;
typedef vector<pl> vpl;

// Maps
typedef unordered_map<ll, ll, custom_hash> umapll;
template <typename K, typename V>
using umap = unordered_map<K, V, custom_hash>;

typedef unordered_set<ll, custom_hash> usetl;
template <typename K>
using uset = unordered_set<K, custom_hash>;

umapll operator+(const umapll& lhs, const umapll& rhs) {
    umapll result = lhs;

    for (const auto& pair : rhs) {
        result[pair.first] += pair.second;
    }

    return result;
}

template <typename Key, typename Value>
Value mget(const std::unordered_map<Key, Value, custom_hash>& map, const Key& key) {
    auto it = map.find(key);
    if (it != map.end()) {
        return it->second;
    }
    return Value{}; // Default-constructed value
}

template <typename K, typename V>
void initmap(umap<K, V>& counts) {
    counts.reserve(250000);
    counts.max_load_factor(0.25);
}

#define RC(typ, expr, x, lo, hi) ({ \
    typ lcret; \
    rep(x, lo, hi) {\
        lcret.push_back(expr); \
    } \
    lcret; \
})

#define LC(typ, expr, x, arr) ({ \
    typ lcret; \
    foreach(x, arr) {\
        lcret.push_back(expr); \
    } \
    lcret; \
})

int dx[4] = {1, 0, -1, 0};
int dy[4] = {0, 1, 0, -1};

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

#define first_st(x, cond, lo, hi) ({ \
    ll _INTERNAL_start = (lo);                \
    ll _INTERNAL_end = (hi);                  \
    ll x;                                               \
    for (x = _INTERNAL_start; x <= _INTERNAL_end; x++) { \
        if (cond) break;                                 \
    }                                                    \
    x;                                                   \
})

#define last_st(x, cond, lo, hi) ({  \
    ll _INTERNAL_start = (lo);                \
    ll _INTERNAL_end = (hi);                  \
    ll x;                                               \
    for (x = _INTERNAL_end; x >= _INTERNAL_start; x--) { \
        if (cond) break;                                 \
    }                                                    \
    x;                                                   \
})

#define any_st(x, cond, lo, hi) ({   \
    bool any_good = false;                            \
    ll _INTERNAL_start = (lo);                \
    ll _INTERNAL_end = (hi);                  \
    ll x;                                               \
    for (x = _INTERNAL_start; x <= _INTERNAL_end; x++) { \
        any_good |= (cond);                           \
    }                                                    \
    any_good;                                         \
})

#define all_st(x, cond, lo, hi) ({   \
    bool all_good = true;                                \
    ll _INTERNAL_start = (lo);                \
    ll _INTERNAL_end = (hi);                  \
    ll x;                                               \
    for (x = _INTERNAL_start; x <= _INTERNAL_end; x++) { \
        all_good &= (cond);                              \
    }                                                    \
    all_good;                                            \
})

// Strings
namespace str {
    string lower(const string& s) {
        string result = s;
        transform(result.begin(), result.end(), result.begin(), ::tolower);
        return result;
    }

    string upper(const string& s) {
        string result = s;
        transform(result.begin(), result.end(), result.begin(), ::toupper);
        return result;
    }

    template <typename T>
    string join(const vector<T>& elements, const string& delimiter) {
        ostringstream oss;
        for (size_t i = 0; i < elements.size(); ++i) {
            if (i != 0) {
                oss << delimiter;
            }
            oss << elements[i];
        }
        return oss.str();
    }

    ll indexof(string s, string s2) {
        auto idx = s.find(s2);
        if (idx == std::string::npos) return -1;
        return ll(idx);
    }

    ll contains(string s, string s2) {
        return indexof(s, s2) != -1;
    }

    int stoi(char ch) {
        return int(ch - '0');
    }

    string slc(const string& s, int start, int end) {
        return s.substr(start, end - start);
    }

    vector<string> split(const string& s, char delimiter) {
        vector<string> result;
        stringstream ss(s);
        string token;

        while (getline(ss, token, delimiter)) {
            result.push_back(token);
        }

        return result;
    }

    string fill(const string& s, int num) {
        string ret = "";
        for (int i = 0; i < num; i++) {
            ret += s;
        }
        return ret;
    }
}

namespace mset {
    template <typename S, typename T>
    void del(S& ss, T x) {
        auto it = ss.find(x);
        if (it == ss.end()) {
            throw std::out_of_range("element not found " + to_str(x));
        }
        ss.erase(it);
    }

    template <typename S, typename T>
    void mset_move(S& ss1, S& ss2, T x) {
        auto ptr = ss1.find(x);
        if (ptr != ss1.end()) {
            ss1.erase(ptr);
            ss2.insert(x);
        }
        else {
            throw std::out_of_range("element not found");
        }
    }

    template <typename T>
    T min(multiset<T>& ss) {
        if (ss.empty()) {
            throw out_of_range("Empty set min");
        }
        return *(ss.begin());
    }

    template <typename T>
    T max(multiset<T>& ss) {
        if (ss.empty()) {
            throw out_of_range("Empty set max");
        }
        return *(ss.rbegin());
    }

    template <typename T>
    T min(set<T>& ss) {
        if (ss.empty()) {
            throw out_of_range("Empty set min");
        }
        return *(ss.begin());
    }

    template <typename T>
    T max(set<T>& ss) {
        if (ss.empty()) {
            throw out_of_range("Empty set max");
        }
        return *(ss.rbegin());
    }

    template <typename T, typename V>
    T min(map<T, V>& ss) {
        if (ss.empty()) {
            throw out_of_range("Empty set min");
        }
        return (ss.begin())->first;
    }

    template <typename T, typename V>
    T max(map<T, V>& ss) {
        if (ss.empty()) {
            throw out_of_range("Empty set max");
        }
        return (ss.rbegin())->first;
    }

    template <typename T>
    T popmax(set<T>& ss) {
        auto val = max(ss);
        ss.erase(val);
        return val;
    }

    template <typename T>
    T popmin(set<T>& ss) {
        auto val = min(ss);
        ss.erase(val);
        return val;
    }
}


typedef multiset<ll> msetl;

// Input
namespace inp {
    ll binary() {
        string s;
        cin >> s;
        ll res = 0;
        for (char c : s) {
            res <<= 1;
            if (c == '1') res |= 1;
        }
        return res;
    }
}

// Printing

void init() {
    ios_base::sync_with_stdio(false), cin.tie(nullptr);
    cout << setprecision(9);
}

template<typename T1, typename T2>
std::ostream& operator<<(std::ostream& os, const std::pair<T1, T2>& p) {
    os << "(" << p.first << ", " << p.second << ")";
    return os;
}

template<typename K, typename V>
std::ostream& operator<<(std::ostream& os, const unordered_map<K, V, custom_hash>& mp)
{
    os << "{ ";
    for (const auto& p : mp) {
        os << p.first << ": " << p.second << ", ";
    }
    os << "}";
    return os;
}

template<typename K, typename V>
std::ostream& operator<<(std::ostream& os, const map<K, V>& mp)
{
    os << "{ ";
    for (const auto& p : mp) {
        os << p.first << ": " << p.second << ", ";
    }
    os << "}";
    return os;
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& v) {
    for (auto it = v.begin(); it != v.end(); ++it) {
        os << *it;
        if (it != v.end() - 1) {
            os << " ";
        }
    }
    return os;
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::set<T>& s) {
    os << "{ ";
    for (const auto& item : s) {
        os << item << " ";
    }
    os << "}";
    return os;
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::multiset<T>& s) {
    os << "{ ";
    for (const auto& item : s) {
        os << item << " ";
    }
    os << "}";
    return os;
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::unordered_set<T, custom_hash>& s) {
    os << "{ ";
    for (const auto& item : s) {
        os << item << " ";
    }
    os << "}";
    return os;
}

template<typename K, typename V>
std::ostream& operator<<(std::ostream& os, const std::unordered_map<K, V>& mp)
{
    os << "{ ";
    for (const auto& p : mp) {
        os << p.first << ": " << p.second << ", ";
    }
    os << "}";
    return os;
}

template<typename S, typename T>
istream& operator>>(istream& input, pair<S, T>& p) {
    input >> p.first >> p.second;
    return input;
}

template<typename T>
istream& operator>>(istream& input, vector<T>& vec) {
    for (auto& element : vec) {
        input >> element;
    }
    return input;
}

// Overloading the << operator for __int128_t
// For some reason, the leetcode compilers do not have this
#ifndef LEETCODE
std::ostream& operator<<(std::ostream& os, const __int128_t& value) {
    // Convert __int128_t to a string representation and output it
    std::string output;
    __int128_t cvalue = value;
    if (cvalue < 0) {
        output.append("-");
        cvalue = -cvalue;
    }
    vector<char> digits;
    while (cvalue > 0) {
        digits.pb(cvalue % 10 + '0');
        cvalue /= 10;
    }
    dep(i, len(digits) - 1, 0) {
        output += digits[i];
    }

    os << output;

    return os;
}

// Overloading the >> operator for __int128_t
std::istream& operator>>(std::istream& is, __int128_t& value) {
    std::string input;
    is >> input;

    value = 0;
    rep(i, 0, len(input) - 1) {
        value = value * 10 + (input[i] - '0');
    }

    return is;
}
#endif

template<typename T>
void print(const T& t) {
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

template<typename T, typename... Args>
void print(const T& t, const Args&... args) {
    std::cout << t << " ";
    print(args...);
}

template<typename T>
void dprint(const T& t) {
    #ifndef ONLINE_JUDGE
    #ifdef DEBUG
    std::cout << t << std::endl;
    #endif
    #endif
}

template<typename T, typename... Args>
void dprint(const T& t, const Args&... args) {
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
    #define dbg(x) {++recur_depth; auto x_=x; --recur_depth; cout<<string(recur_depth, '\t')<<__func__<<":"<<__LINE__<<"\t"<<#x<<" = "<<x_<<endl;}
    #else
    #define dbg(x)
    #endif
#else
    #define dbg(x)
#endif



ll MOD = 998244353LL;
// ll MOD = 1000000007;

ll mod(ll a, ll p) {
    if (p > 0) {
        return (a % p + p) % p;
    }
    return a;
}

ll mod(ll a) {
    return mod(a, MOD);
}

ll cmul(ll a, ll b) {
    if (b == 0) return 0;
    if (b > 0) {
        if (a >= LONG_LONG_MAX / b) {
            return LONG_LONG_MAX;
        }
        else if (a <= LONG_LONG_MIN / b) {
            return LONG_LONG_MIN;
        }
        return a * b;
    }
    // b is negative
    if (a <= LONG_LONG_MAX / b) {
        return LONG_LONG_MAX;
    }
    else if (a >= LONG_LONG_MIN / b) {
        return LONG_LONG_MIN;
    }
    return a * b;
}

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
        return std::accumulate(a.begin() + start, a.begin() + end + 1, T(0));
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
    vector<T> cumsum(const vector<T>& a, bool reverse=false) {
        vector<T> ret(a);
        if (reverse) {
            dep(i, len(a) - 2, 0) {
                ret[i] += ret[i + 1];
            }
        } else {
            rep(i, 1, len(a) - 1) {
                ret[i] += ret[i - 1];
            }
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

namespace nt {
    vl primes;
    vl is_composite;
    bool sieve_done = false;

    void do_sieve(ll max_prime) {
        is_composite.resize(max_prime + 1);
        rep(d, 2, max_prime) {
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

    bool is_prime(ll n) {
        // Checks if n is prime
        if (n <= 1) {
            return false;
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

    ll sum_digits(ll n, ll b) {
        int sum = 0;
        while (n > 0) {
            sum += n % b;
            n /= b;
        }
        return sum;
    }

    vl get_digits(ll n, ll b, ll pad=-1) {
        vl ans;
        while (n > 0) {
            ans.push_back(n % b);
            n /= b;
        }
        while (len(ans) < pad) {
            ans.pb(0);
        }
        return ans;
    }

    ll digits_to_num(const vl& digs, ll b) {
        ll s = 0;
        dep(i, digs.size() - 1, 0) {
            s *= b;
            s += digs[i];
        }
        return s;
    }

    // Function to calculate (base^exponent) % modulus using repeated squaring
    ll pow(ll base, ll exponent, ll modulus=MOD) {
        base = mod(base, modulus);
        ll result = 1;

        while (exponent > 0) {
            // If the exponent is odd, multiply the result by base
            if (exponent & 1) {
                if (modulus > 0) {
                    result = (result * base) % modulus;
                }
                else {
                    result = cmul(result, base);
                }
            }
            exponent >>= 1;
            if (exponent == 0) {
                break;
            }

            // Square the base and reduce the exponent by half
            if (modulus > 0) {
                base = (base * base) % modulus;
            }
            else {
                base = cmul(base, base);
            }
        }

        return result;
    }

    ll inv(ll x, ll y) {
        ll p = y;

        ll ax = 1;
        ll ay = 0;
        while (x > 0) {
            ll q = y / x;
            tie(ax, ay) = make_tuple(ay - q * ax, ax);
            tie(x, y) = make_tuple(y % x, x);
        }

        return mod(ay, p);
    }

    ll mdiv(ll x, ll y, ll m=MOD) {
        if (m <= 0) {
            return x / y;
        }
        x = mod(x, m);
        y = mod(y, m);
        return mod(x * inv(y, m), m);
    }

    ll v_p(ll x, ll p) {
        ll res = 0;
        while (x % p == 0) {
            ++res;
            x /= p;
        }
        return res;
    }

    ll factorial(ll x) {
        ll p = 1;
        rep(i, 1, x) {
            p *= i;
            p = mod(p);
        }
        return p;
    }

    bool is_pow_of_2(ll n) {
        return (n > 0) && ((n & (n - 1)) == 0);
    }

    ll phi(ll n) {
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

    ll num_divisors(ll n) {
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

    ll sum_divisors(ll n) {
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

    umapll primeFactorization(ll n) {
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
    bool factorial_computed = false;
    void precompute_fac(ll n, ll m = MOD) {
        factorial.resize(n + 1);
        factorial[0] = 1;
        rep(i, 1, n) {
            factorial[i] = mod(factorial[i - 1] * i, m);
        }
        factorial_computed = true;
    }

    ll choose(ll n, ll k, ll m=MOD) {
        if (k > n) return 0;

        ll ans = mdiv(factorial[n], factorial[k], m);
        return mdiv(ans, factorial[n - k], m);
    }
}

using namespace nt;
using namespace combo;

void solve() {
    ll n; cin >> n;
    vl a(n); cin >> a;

    sort(a);
    ll ans = 0;

    function<void(ll, ll, ll)> func = [&](ll start, ll end, ll k) {
        if (end < start) return;
        if (k < 0) return;

        ll n_zeros = first_st(i, (a[i] & (1LL << k)) > 0, start, end) - start;
        ll n_tot = end - start + 1;
        ll n_ones = n_tot - n_zeros;

        ll idx = start + n_zeros;
        ll ssq = 0;
        while (idx <= end) {
            ll idx2 = first_st(ii, a[ii] != a[idx], idx, end);
            ssq = mod(ssq + (idx2 - idx) * (idx2 - idx));
            idx = idx2;
        }

        bool is_zero_prefix = (a[start] >> (k + 1)) == 0;

        // Both people have 1s
        ans = mod(ans + 2 * (n_ones * n_ones - ssq));
        // Alice 1 Bob 0
        ans = mod(ans + (2 + 2 * is_zero_prefix) * n_ones * n_zeros);
        // Alice 0 Bob 1
        ans = mod(ans + (1 + 2 * is_zero_prefix) * n_zeros * n_ones);
        if (ans > 0) {
            dprint("(k, start, end)", k, start, end, "ans=", ans);
        }

        // Recurse
        func(start, start + n_zeros - 1, k - 1);
        func(start + n_zeros, end, k - 1);
    };

    func(0, n - 1, 30);

    // Get the same people on board
    ll same_ans = 0;
    auto counts = counter(a);
    ll prob = 0;
    foreachp(val, cnt, counts) {
        ll num_moves = sum_digits(val, 2);
        // 1->2
        // 2->3
        // 3->4
        if (num_moves < 3) {
            num_moves = num_moves + 1;
        }
        else {
            num_moves = 2 * (num_moves - 1);
        }

        same_ans += mod(mod(num_moves * cnt) * cnt);
        same_ans = mod(same_ans);
        // dprint(val, cnt, same_ans);
        prob = mod(prob + mod(cnt * cnt));
    }

    prob = mod(mod(n * n) - prob);
    dprint("Prob=", prob);
    ans = mod(ans - 2 * prob);
    dbg(ans); dbg(same_ans);

    ll final_ans = mdiv(ans + same_ans, n * n);
    print(final_ans);
}

int main() {
    init();
    int t; cin >> t;
    cep(t) solve();
    return 0;
}