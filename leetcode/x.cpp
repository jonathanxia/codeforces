// #include<lib/common.h>
#include <bits/stdc++.h>
#include <sstream>
#include <functional>
#include <cmath>

using namespace std;

//  Definition of the macro.
#define ass(a, b, x, y) (tie(a, b) = make_tuple(x, y));
#define ordered(x, y, z) ((x) <= (y) && (y) <= (z))

template <typename T, typename S>
void chkmin(T& lhs, S rhs) {
	lhs = min(lhs, T(rhs));
}
template <typename T, typename S>
void chkmax(T& lhs, S rhs) {
	lhs = max(lhs, T(rhs));
}

// Because unsigned sizes are absolutely stupid
// Got burned on 1841C
template <typename T>
inline int len(const T& v) {
    return int(v.size());
}

#define to_str to_string
#define pb push_back
#define mp make_pair
#define ALL(x) (x).begin(), (x).end()

typedef long long ll;

// Looping
#define rep(i, d, u) for(ll i = (d); i <= (u); ++i)
#define dep(i, u, d) for(ll i = (u); i >= (d); --i)
#define irep(i, d, u) for(i = (d); i <= (u); ++i)
#define idep(i, u, d) for(i = (u); i >= (d); --i)
#define srep(i, d, u, s) for(ll i = (d); i <= (u); i += s)
#define cep(t) while(t--)
#define foreach(i, c) for(auto& i : c)
#define foreachp(k, v, c) for (auto& [k, v] : c)

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

typedef vector<vector<ll>> vvl;
typedef vector<vector<string>> vvs;
typedef vector<ll> vl;
typedef vector<bool> vb;
typedef pair<ll, ll> pl;
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

#define LC(expr, x, arr) ({                                          \
    using LCx_t = decltype(arr)::value_type;                         \
    LCx_t x;                                                         \
    using LCexpr_t = std::remove_reference<decltype(expr)>::type;    \
    vector<LCexpr_t> lcret;                                          \
    foreach (LC_i, arr) {                                            \
        x = LC_i; /*Using LC_i and then x = LC_i pacifies -Wshadow*/ \
        lcret.push_back(expr);                                       \
    }                                                                \
    lcret;                                                           \
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
    void mset_del(S& ss, T x) {
        auto it = ss.find(x);
        if (it == ss.end()) {
            throw std::out_of_range("element not found");
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
}


typedef multiset<ll> msetl;

// Input
namespace inp {
    long long binary() {
        string s;
        cin >> s;
        long long res = 0;
        for (char c : s) {
            res <<= 1;
            if (c == '1') res |= 1;
        }
        return res;
    }

    void array1(vl& arr, int n) {
        rep(i, 1, n) {
            cin >> arr[i];
        }
    }
}

// Printing

void init() {
    ios_base::sync_with_stdio(false), cin.tie(nullptr);
}

template<typename T>
void print(const T& t) {
    #ifdef INTERACTIVE
    std::cout << t << std::endl;
    #else
    std::cout << t << "\n";
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
#endif

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

template<typename T1, typename T2>
std::ostream& operator<<(std::ostream& os, const std::pair<T1, T2>& p) {
    os << "(" << p.first << ", " << p.second << ")";
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

template<typename T>
istream& operator>>(istream& input, vector<T>& vec) {
    for (auto& element : vec) {
        input >> element;
    }
    return input;
}

template<typename S, typename T>
istream& operator>>(istream& input, pair<S, T>& p) {
    input >> p.first >> p.second;
    return input;
}

#define METHOD countPalindromePaths

class Solution {
public:
    long long countPalindromePaths(vector<int>& parent, string s) {
        ll n = len(parent);
        vvpl graph(n);
        rep(i, 1, n - 1) {
            ll e = 1 << (s[i] - 'a');
            graph[i].pb({parent[i], e});
            graph[parent[i]].pb({i, e});
        }

        umapll counts;
        
        auto dfs = [&](auto&& self, ll node, ll p, ll tot) -> void {
            counts[tot]++;
            foreachp(child, edge, graph[node]) {
                if (child == p) continue;
                self(self, child, node, tot ^ edge);
            }
        };
        dfs(dfs, 0, -1, 0);

        ll ans = 0;
        // Count same guys
        foreachp(k, v, counts) {
            ans += v * (v - 1) / 2;
        }
        // Count diff guys
        ll ans1 = 0;
        foreachp(k, v, counts) {
            rep(i, 0, 25) {
                ll k1 = k ^ (1 << i);
                ans1 += mget(counts, k1) * v;
            }
        }

        return ans + ans1 / 2;
    }
};

#ifdef DEBUG
int main() {
    Solution s;
    vi parent = {-1,0,0,1,1,2};
    string st = "acaabc";
    print(s.METHOD(parent, st));
    return 0;
}
#endif